# Usage: ./this.py 'hdfs://login.hpc.recolic.org:54310/prepared-totalCheckins.txt' 1 30000
#
# DataFile format:
# <uid> \t <x> \t <y>

######################## Import libraries ##########################
from pyspark.context import SparkContext
from pyspark.sql.session import SparkSession
sc = SparkContext()
spark = SparkSession(sc)
import numpy, sys
from pyspark.mllib.clustering import BisectingKMeans, BisectingKMeansModel
from itertools import chain, combinations
all_sublists_impl = lambda l: list(chain(*(combinations(l, i) for i in range(len(l) + 1))))[1:]
all_sublists = lambda l: all_sublists_impl(list(l)[:7]) # too many elements booms the combination num

######################## Read commandline args ##########################
fileUrl = 'hdfs://login.hpc.recolic.org:54310/prepared-totalCheckins.txt'
iterations = 1
partitions = 30000 # parsedData.countApprox(1000) / 32

try:
    fileUrl = sys.argv[1]
    iterations = int(sys.argv[2])
    partitions = int(sys.argv[3])
except:
    pass

print('Using: fileUrl={}, iterations={}, partitions={}'.format(fileUrl, iterations, partitions))

######################## Do actual work ##########################
data = sc.textFile(fileUrl).distinct().map(lambda line: line.split()).map(lambda line: [int(line[0]), float(line[1]), float(line[2])])
dataInNumpy = data.map(lambda line: numpy.array(line[1:]))

model = BisectingKMeans.train(dataInNumpy, partitions, maxIterations=iterations)
print("DEBUG: Bisecting K-means Cost = " + str(model.computeCost(dataInNumpy)))

# (uid, tag)
taggedActivities = data.map(lambda line: line[0]).zip(model.predict(dataInNumpy)).distinct()

# (uid, tag) => (uid, [tags, ...])         => (uid, combinations), ... => (tag1, [uid1, uid2, ...]), ([tag1, tag2], [uid2, uid3, ...])
tagsToUsers = taggedActivities.groupByKey().flatMapValues(all_sublists).groupBy(lambda kv: kv[1]).mapValues(lambda l: [e[0] for e in l])

def recommand(tagsAndUsers):
    tags, users = tagsAndUsers
    for user in users:
        usersWithoutThisOne = list(filter(lambda uid: uid != user, users))
        # Results with longer tags are preferred.
        yield (user, (usersWithoutThisOne, len(tags)))

def mergeRecommandations(recommandations):
    finalResults = []
    rs = list(recommandations)
    rs.sort(key=lambda ul: ul[1], reverse=True)
    for recommand in rs:
        users, tagsLength = recommand
        finalResults += users
        if len(finalResults) > 10:
            break
    return finalResults

userToFriends = tagsToUsers.flatMap(recommand).groupByKey().mapValues(mergeRecommandations)

print('DONE. Example result (take 30): ')
print(userToFriends.take(30))
