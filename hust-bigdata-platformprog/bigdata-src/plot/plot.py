
import sys
with open(sys.argv[1]) as f:
    lines = f.read()

def printFilter(uid):
    return True

newLines = []
for line in lines.split('\n'):
    if line == '':
        continue
    try:
        uid, y, x = tuple(line.split())
        uid, y, x = int(uid), float(y), float(x)
        if not printFilter(uid):
            continue
        if abs(y) > 90 or abs(x) > 180:
            continue
        newLines.append(str(x) + '  ' + str(y))
    except:
        raise

with open(sys.argv[2], 'w+') as f:
    f.write('\n'.join(newLines))

