#!/bin/bash
echo "Constructing URLs..."
grep "data-url" rr.html | sed 's#.*"/##' | sed 's#">$##' | sed 's#^fiction#https://www.royalroad.com/fiction#' > linkPostFix.html
rm rr.html
