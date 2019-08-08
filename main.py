import requests
from contextlib import closing
from bs4 import BeautifulSoup

def getPage(fictionUrl):
    pageResponse = requests.get(fictionUrl)
    return pageResponse

def getTitle(pageResponse):
    soupPage = BeautifulSoup(pageResponse.content, 'html.parser')
    title = soupPage.find('h1', property="name").string
    return title

def getAuthor(pageResponse):
    soupPage = BeautifulSoup(pageResponse.content, 'html.parser')
    author = soupPage.find('h4', property="author").find('a').string
    return author

def getCoverUrl(pageResponse):
    soupPage = BeautifulSoup(pageResponse.content, 'html.parser')
    img = soupPage.find('div', class_="row fic-header").find('img')
    coverUrl = img.get('src')
    if coverUrl.startswith("/"):
        coverUrl = "https://www.royalroad.com" + coverUrl
    return coverUrl

# gets table that contain partial chapter links
def getTable(pageResponse):
    soupPage = BeautifulSoup(pageResponse.content, 'html.parser')
    chapterTable = soupPage.find(id="chapters")
    return chapterTable

# gets partial links from above table
def getChPaths(chapterTable):
    chPaths = []
    for link in chapterTable.find_all('a', href=True):
        chPaths.append(link.get('href'))
    return chPaths

# turns incomplete chapter paths from the table into full links
def constructLinks(chPaths):
    chLinks = []
    for path in chPaths:
        chLinks.append("https://www.royalroad.com" + path)
    return chLinks

fictionId = input("Enter fiction ID here: ")
fictionUrl = "https://www.royalroad.com/fiction/" + fictionId

pageResponse = getPage(fictionUrl)

title = getTitle(pageResponse)
author = getAuthor(pageResponse)
coverUrl = getCoverUrl(pageResponse)

chapterTable = getTable(pageResponse)
chPaths = getChPaths(chapterTable)
chLinks = constructLinks(chPaths)
