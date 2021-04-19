import sys
with open(sys.argv[1]) as f:
    lines = f.read()

newLines = []
for line in lines.split('\n'):
    if line == '':
        continue
    try:
        ar = line.split()
        ar = [ar[0]] + ar[2:-1]
        [float(e) for e in ar] # Verify
        newLines.append('\t'.join(ar))
    except:
        print('DEBUG: LINE=' + line)
        raise

with open(sys.argv[2], 'w+') as f:
    f.write('\n'.join(newLines))
