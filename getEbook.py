#!/usr/bin/env python3
import requests
from bs4 import BeautifulSoup
from ebooklib import epub
import click


def getPage(fictionUrl):  # Todo: error handing
    headers = {'User-Agent': "App-Scraper"}
    pageResponse = requests.get(fictionUrl, headers)
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


def getChTitle(soupPage):
    chTitle = soupPage.find('h1').string
    return chTitle


def getChContent(soupPage):
    chContent = soupPage.find('div', class_="chapter-content").get_text()
    return chContent


# TO DO: make the two loops one loop
# gets chapter links in chLinks
def getChLinks(soupPage):
    chTable = soupPage.find(id="chapters")

    chPaths = []
    for link in chTable.find_all('a', href=True):
        chPaths.append(link.get('href'))

    chLinks = []
    for path in chPaths:
        chLinks.append("https://www.royalroad.com" + path)

    return chLinks


def createBook(outfile, title, author, chLinks):
    # create book and set metadata
    print('Creating Ebook...')
    book = epub.EpubBook()
    book.set_title(title)
    book.set_language('en')
    book.add_author(author)

    chs = []
    # tocLinks = []
    i = 0
    for link in chLinks:
        j = i + 1
        filename = f"chap_{j}.xhtml"

        soupPage = getPage(link)  # todo: some kind of input sanitization
        chTitle = getChTitle(soupPage)
        # chTitleXml = chTitle.replace(' ', '_')
        chContent = getChContent(soupPage)
        # print(chContent)

        print(f'Getting Chapter {j}: {chTitle}')

        # Add ch to book
        chs.append(epub.EpubHtml(title=chTitle, file_name=filename))
        chs[i].content = chContent
        book.add_item(chs[i])
        book.toc.append(chs[i])
        book.spine.append(chs[i])

        i += 1

    # adds ncx and nav files
    book.add_item(epub.EpubNcx())
    book.add_item(epub.EpubNav())

    # define CSS style
    # style = 'BODY {color: white;}'
    nav_css = epub.EpubItem()

    # add CSS file
    book.add_item(nav_css)

    if outfile == '' or outfile is None:
        outfile = title.replace(' ', '_')

    epub.write_epub(f'{outfile}.epub', book, {})
    print(f'Created {outfile}.epub')


@click.command()
@click.argument('fiction_id')
@click.option(
    '-o', '--outfile',
    help='Name of file to output to. Do not include extension.',
)
def main(fiction_id, outfile):
    fictionUrl = "https://www.royalroad.com/fiction/" + fiction_id

    soupPage = getPage(fictionUrl)

    title = getTitle(soupPage)
    author = getAuthor(soupPage)
    # coverUrl = getCoverUrl(soupPage)

    chLinks = getChLinks(soupPage)

    createBook(outfile, title, author, chLinks)


main()