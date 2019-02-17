# import the necessary packages
from PIL import Image
import pytesseract
import argparse
import cv2
import os
from googletrans import Translator
import textwrap
# construct the argument parse and parse the arguments
pytesseract.pytesseract.tesseract_cmd = 'C:\\Program Files (x86)\\Tesseract-OCR\\tesseract.exe'
trans=Translator()
arg_parse = argparse.ArgumentParser()
arg_parse.add_argument("-r", "--resim", required=True, help="OCR yapilacak resmin yolu")
arg_parse.add_argument("-i", "--islem",  help="resim uzerinde ilave islem yapmak için")
args = vars(arg_parse.parse_args())
resim = cv2.imread(args["resim"])
gray = cv2.cvtColor(resim, cv2.COLOR_BGR2GRAY)
#Kullanıcı -i parametresi girerse ; 
if args["islem"] == "thresh" :
	gray = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
elif args["islem"] == "blur" :
	gray = cv2.medianBlur(gray, 3)
dosya_Adi = "{}.png".format(os.getpid())
cv2.imwrite(dosya_Adi, gray)
metin = pytesseract.image_to_string(Image.open(dosya_Adi))
metin=textwrap.fill(metin, 25)
os.remove(dosya_Adi)
F = open("dene.txt","w")
F.write("kerem \n")
F.write(str(metin)) 
translated=trans.translate(metin,dest='tr')
F.close()
print(metin)
print("*****")
print(translated.text)

cv2.waitKey(0)
cv2.destroyAllWindows()
