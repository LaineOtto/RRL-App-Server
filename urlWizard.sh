#!/bin/bash
echo "Constructing URLs"
cat rr.html | grep "data-url" | sed 's#.*"/##' | sed 's#">$##' | sed 's#^fiction#https://www.royalroad.com/fiction#' > linkPostFix.html
rm rr.html
