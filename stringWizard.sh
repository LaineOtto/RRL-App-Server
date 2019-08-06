#!/bin/bash
echo "Constructing URLs..."
# Grabs all ch urls and outputs them to linkPostFix.txt
grep "data-url" rr.html | sed 's#.*"/##' | sed 's#">$##' | sed 's#^fiction#https://www.royalroad.com/fiction#' > linkPostFix.txt

# Grabs title, author, and cover img url
grep "<h1 class=\"font-white\" property=\"name\">" rr.html | sed 's#^.*name">##' | sed 's#<.*$##' > fictionData.txt
grep "<a href=\"/profile/" rr.html | head -n1 | sed 's#^.*e">##' | sed 's#<.*$##' >> fictionData.txt
coverStr=$(grep "id=\"cover" rr.html | sed 's#.*src=\"##' | sed 's#\".*\$##' | sed 's#".*$##')
if [[ $coverStr == /* ]]; then # Default cover image has a different path
  coverStr="https://www.royalroad.com"$coverStr
fi
echo $coverStr >> fictionData.txt

# No extra files
rm rr.html
