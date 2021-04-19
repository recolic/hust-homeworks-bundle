#!/usr/bin/fish

for f in (ls)
    set shit ( echo "$f" | perl -ne 'print lc' )
    test "$f" = "$shit"; or mv $f $shit
end
