import requests
from bs4 import BeautifulSoup
from ebooklib import epub


def getPage(fictionUrl):  # Todo: error handing
    pageResponse = requests.get(fictionUrl)
    soupPage = BeautifulSoup(pageResponse.content, 'html.parser')
    return soupPage


def getTitle(soupPage):
    title = soupPage.find('h1', property="name").string
    return title


def getAuthor(soupPage):
    author = soupPage.find('h4', property="author").find('a').string
    return author


def getCoverUrl(soupPage):
    img = soupPage.find('div', class_="row fic-header").find('img')
    coverUrl = img.get('src')
    if coverUrl.startswith("/"):
        coverUrl = "https://www.royalroad.com" + coverUrl
    return coverUrl



# gets table that contain partial chapter links
def getTable(soupPage):
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


def createBook(title, author, chLinks):
    chs = []


fictionUrl = "https://www.royalroad.com/fiction/" + \
    input("Enter fiction ID here: ")  # Todo: verify this input

soupPage = getPage(fictionUrl)

title = getTitle(soupPage)
author = getAuthor(soupPage)
coverUrl = getCoverUrl(soupPage)

chapterTable = getTable(soupPage)
chPaths = getChPaths(chapterTable)
chLinks = constructLinks(chPaths)

createBook(title, author, chLinks)

for link in chLinks:
    print(link)

# print(chLinks)
