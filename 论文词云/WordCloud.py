###################################
#  步骤：
#  1.读取PDF文件并转为txt文件
#  2.合并txt文件为result.txt
#  3.读取result.txt文件并进行划分得到词云
#
####################################

import os
import sys, getopt
import jieba
import wordcloud
from io import StringIO
from pdfminer.pdfinterp import PDFResourceManager 
from pdfminer.pdfinterp import PDFPageInterpreter
from pdfminer.converter import TextConverter
from pdfminer.layout import LAParams
from pdfminer.pdfpage import PDFPage
from imageio import imread

# PDFPATH：PDF格式论文绝对路径
PDFPATH = 'C:/Users/LinYingyu/Downloads/20182831035/Paper/'
TXTPATH = PDFPATH+'TEXT/'
# WORDCLOUDPATH：最终词云绝对路径
WORDCLOUDPATH = PDFPATH+'PAPER-WordCloud.png'

from pdfminer.pdfparser import PDFParser

def convert(fname, pages=None):
    if not pages:
        pagenums = set()
    else:
        pagenums = set(pages)

    output = StringIO()
    # 创建一个PDF资源管理器对象来存储共赏资源
    manager = PDFResourceManager()
    # 创建一个PDF设备对象
    converter = TextConverter(manager, output, laparams=LAParams())
    # 创建一个PDF解释器对象
    interpreter = PDFPageInterpreter(manager, converter)
    
    #打开源pdf文件
    infile = open(fname,'rb')
    
    #对pdf每一页进行分析
    for page in PDFPage.get_pages(infile, pagenums):
        interpreter.process_page(page)
    infile.close()
    converter.close()
    
    #得到每一页的txt文档
    text = output.getvalue()
    output.close
    return text


# converts all pdfs in directory pdfDir, saves all resulting txt files to txtdir
def convertMultiple(pdfDir, txtDir):
    #判断是否有储存的文件夹，如果有则pass，没有则创建
    if os.path.exists(txtDir):
        pass
    else:
        os.makedirs(txtDir)
    #判断读取pdf是否需要密码
    if pdfDir == "": pdfDir = os.getcwd() + "/"  # if no pdfDir passed in
        
    #遍历文件夹下每一个pdf文件
    for pdf in os.listdir(pdfDir):  # iterate through pdfs in pdf directory
        fileExtension = pdf.split(".")[-1]
        #判断是否该文件夹下的文件是否是pdf文件
        if fileExtension == "pdf" or fileExtension == "PDF":
            #构建pdf的完全路径
            pdfFilename = pdfDir + pdf
            text = convert(pdfFilename)  # get string of text content of pdf
            #构建存储文件的目标路径
            textFilename = txtDir + '/' +pdf[:-4]+ ".txt"
            #将解析得到的pdf文件写入对应的txt文件
            f = open(textFilename,'a',encoding='utf-8')
            f.write(text)
            f.close()

def PDFTOTXT(pdfpath,txtpath):
    #调用pdf解析文件
    convertMultiple(pdfpath,txtpath)

#多个TXT合并为同一个
def TOATEXT(txtpath):
    #获取目标文件夹的路径
    filedir = txtpath
    #获取当前文件夹中的文件名称列表
    filenames = os.listdir(filedir)
    #打开当前目录下的result.txt文件，如果没有则创建
    f=open(txtpath+'A-result.txt','w',encoding='utf-8')
    #先遍历文件名
    for filename in filenames:
        filepath = filedir+filename
        #遍历单个文件，读取行数
        for line in open(filepath,encoding='utf-8'):
            f.writelines(line)
            f.write('\n')
    f.close()
    return txtpath+'A-result.txt'

#词云
def WORDCLOUD(txtpath,wordcloudpath):
    txt=open(txtpath,"r",encoding="utf-8")
    t=txt.read()
    txt.close()
    word=jieba.lcut(t)
    excludes=['a','b','th','an','es','i']
    wc=" ".join(word)
    w=wordcloud.WordCloud(font_path="msyh.ttc",background_color="white",\
                      max_words=50,stopwords=excludes)
    w.generate(wc)
    w.to_file(wordcloudpath)

if __name__ == "__main__":
    PDFTOTXT(PDFPATH,TXTPATH)
    Totaltxt=TOATEXT(TXTPATH)
    WORDCLOUD(Totaltxt,WORDCLOUDPATH)
