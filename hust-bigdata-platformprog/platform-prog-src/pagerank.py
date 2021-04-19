# spark-submit --master spark://login.hpc-lan.recolic.org:7077 pagerank.py hdfs://login.hpc-lan.recolic.org:54310/first-soc-Epinions1.txt 10


from pyspark.sql import SparkSession
spark = SparkSession.builder.appName("TestApp-l").getOrCreate()

import operator

def computeContribs(urls, prevRnk):
    for url in urls:
        yield (url, prevRnk / len(urls))

def oneIteration():
    global ranks
    contribs = links.join(ranks).flatMap(lambda ele: computeContribs(ele[1][0], ele[1][1]))
    ranks = contribs.reduceByKey(operator.add).mapValues(lambda rank: rank * 0.8 + 0.2)

import sys
try:
    # default value
    loopCount = 1
    filePath = 'gs://dataproc-14d20d7c-6fe3-4418-b9f7-e3220843f4e7-asia-east2/first-soc-Epinions1.txt'
    loopCount = int(sys.argv[1])
    filePath = sys.argv[2]
except:
    pass

print('Using config: loopCount = {}, filePath = {}.'.format(loopCount, filePath))

lines = spark.read.text(filePath).rdd.map(lambda r: r[0])
links = lines.map(lambda urls: tuple(urls.split())).distinct().groupByKey().cache()
ranks = links.map(lambda url_neighbors: (url_neighbors[0], 1.0))

for i in range(loopCount):
    oneIteration()
    ranks.first() if i % 50 == 49 else 0

samples = ranks.sortBy(lambda ele: -ele[1]).take(30)
map(samples, lambda e : print('RANK(%s) = %s' % e))

spark.stop()

