# How to write your own shell?

## Giris

Bu projede belli sinirlamalar ile kendi shell'imizi yazacagiz. Isin kod kismina gecis yapmadan once ilk olarak terminal'in calisma mantigini ve  komutlarinin nasil calistigini iyi bilmek gerekiyor. Bu projeyi yapmaya niyetlendiyseniz zaten bu zamana kadar terminalle fazlasiyla icli disli oldugunuzu dusunuyorum. Yine de baslamadan once neyin nasil calistigini bilmek iyi bir secim olacaktir.

### Terminal Nedir?
---

Terminal en basitinde, shell'in calistirilabilir dosyalariyla iletisim kurmanizi saglayan bir emulatordur. Mac kullanicisiysaniz iterm, windows kullanicisiysaniz powershell, linux kullanicisiysaniz ise gnome-terminal gibi sayisiz terminal ile karsilasmissinizdir. 

### Terminal Dosya Sistemi
---
Isletim sistemleri aslinda arkaplanda tum dosyalarinizi, tum klasorlerinizi bir agac yapisinda tutar. Sizin mac'te kullandiginiz finder, windowsta kullandiginiz files gibi uygulamalar sadece bu agac yapisini daha anlasilir sekilde dolasmanizi saglarlar.

![enter image description here](https://linuxcommand.org/images/file_manager.jpg)

Terminalde ise bu agac yapisinda dolasabilmeniz icin **cd** komutunu kullanabiliriz. Oldugumuz konumu gorebilmek icin ise **pwd** komutunu kullanabiliriz. 

### **pwd**
---
Terminalde hazir olarak calismakta oldugumuz dizini grafiksel olarak goremiyoruz. Bu yuzden calismakta oldugumuz konumu metinsel olarak goruntuleme yoluna gitmeliyiz. Bunu da **pwd** komutu ile gerceklestirebiliriz. 
```bash
[emreakdik@dell Desktop]$ pwd
/home/Desktop
```
Neredeyse butun terminallerde ilk acilis ekraninda dizin home klasoru olarak belirlenmis durumdadir. Oldugumuz terminaldeki dosya ve klasorleri goruntulemek icin ise basitce **ls** komutunu kullanabiliriz.

### **cd**
---
Terminal uzerinden oldugumuz konumu degistirmek icin change directory komutunu kullaniriz. Bu degistirme islemini basitce cd komutundan sonra gidecegimiz konumun yolunu yazarak yapabiliriz ama bu konuda iki farkli yontem vardir. Bu yontemler ise relative path ve absolute path yontemleridir. Bu ikisini basitce aciklamak gerekirse:

**Relative Path:**

Ornegin terminalimizde dizin olarak Desktop konumunda olalim ve desktopta var olan **minishell** klasorune gitmek isteyelim. Tek yapmamiz gereken asagidaki komutu kullanmaktir.

```bash
[emreakdik@dell Desktop]$ cd minishell
```
Yukaridaki sekilde komut kullanirsak, terminal bizim icin oldugumuz konumda minishell klasorunu arar ve eger varsa calisma dizinimizi minishell klasoru olarak degistirir. 

**Absolute Path:**

Diyelim ki documents dizinindeyiz ve Desktop dizinindeki minishell klasorune erismek istiyoruz. Eger bunun icin yukaridaki gibi bir komut kullanirsak klasorun bulunamadigina dair bir hata mesaji ile karsilasacagiz. Cunku relative path vererek kullandigimiz cd komutunda, terminal bizim icin o an oldugumuz dizinde arama yapmaktadir ve minishell klasoru Documents dizininde degil Desktop dizininde. Iste bunun gibi durumlarda Absolute Path kullanimi bizi kurtarmaktadir.

```bash
[emreakdik@dell Desktop]$ cd /Users/emreakdik/Desktop/minishell
[emreakdik@dell minishell]$ 
```
Absolute Path kullandigimiz durumda hangi konumda olursak olalim terminal bizim icin kok dizinden baslar ve verdigimiz yolu takip ederek istedigimiz klasore ulasmamizi saglar.

### Dizinler
---
Kendi shell'imizi yazarken kok dizinimizde bulunan bazi klasorlerin icerigine hakim olmamiz gerekecek. Bu yuzden bu klasorlerin iceriklerini basitce ozetleyecegim.


| dizin | aciklama |
|--|--|
| **/** | Bu dizin agac sistemimizin yani klasorlerimizin baslangic dizinidir. Bu yuzden kok dizin(root) denir. |
|**/boot:**  | Bu dizin isletim sistemimizin yukleyicisinin oldugu klasordur.
| **/etc:** | Bu dizinde ise isletim sistemimizin konfigurasyon dosyalarinin oldugu dizindir. |
| **/bin, /usr/bin** | Bu dizinlerde sistem icin gereken calistirilabilir dosyalar bulunmaktadir. Ayni zamanda usr/bin dizininde ise kullanici icin olan calistirilabilir dosyalar vardir. Kendi shell'imizi yazarken kullandigimiz komutlari genel olarak bu dizinlerde arayacagiz. 
| **/sbin, /usr/sbin** | Bu dizinde ise admin kullanici icin olan calistirilabilir dosyalar vardir. |

### Environment Variables
---
**Çevre değişkenleri, çevresel değişkenler** ya da **ortam değişkenleri** (ing. environment variable), işletim sistemi seviyesinde konfigüre edilebilen ve bilgisayar işlemleri bilgisayar tarafından erişilebilen değişkenlerdir. Çoğu kez belli programların ve dosyaların konumlarını  ve birden fazla işlem tarafından kullanılabilen bilgi ve ayarları tutmak için kullanılırlar. 

Kendi yazdigimiz shell'de ise bulunan ve ayiklanan komutlar cevre degiskenlerinde var olan PATH degiskenindeki yollar uzerinden aranip o sekilde calistirilabilir dosyalari calistirilacaktir.

Terminalde cevre degiskenlerini gormek icin **env** komutunu kullanabiliriz. Cevre degiskenleri her terminali kapatip actigimizda tekrar varsayilan hale dondurulurler.

Ornek:
```bash
[emreakdik@dell Desktop]$ env
```

### Builtin Commands
---
Kendi shell'imizi yazarken, bazi komutlari shell'imizin icine gomecegiz ve kendi kodlarimizdan calismasini saglayacagiz. Bu komutlari ise asagidaki gibidir:

- cd (hem relative path ile hem absolute path ile calisacak)
- pwd
- echo (-n secenegi ile)
- export
- unset
- env
- exit

Proje kurallarina gore yukaridaki komutlardan echo disinda hicbirine bir secenek eklememize gerek yok. 
cd, pwd ve env komutlarini yukarida acikladigim icin direkt olarak digerlerine gecis yapacagim.

**echo:** Kendisine verilen argumanlari standart ciktiya yazdirir ve sonuna newline ekler. "-n" flagi ile birlikte sonuna newline eklemez.

 **export:** 	Cevre degiskenlerine bir degisken eklemek icin kullanilir. Ornegin 
```bash
[emreakdik@dell Desktop]$ export emre=akdik
```
Eklediginiz cevre degiskenini gormek icin asagidaki gibi echo komutunu kullanabilirsiniz.
```bash
[emreakdik@dell Desktop]$ echo $emre
```
**unset:** Cevre degiskenlerinden bir degiskeni silmemize yarar. Ornegin:
```bash
[emreakdik@dell Desktop]$ unset emre
```
**exit**: oldugumuz terminali kapatmamizi saglar.

### Redirection
---
Redirection,  komut satırı arayüzlerinde önemli bir tekniktir ve kullanıcıların komutların girdi ve çıktılarını başka yerlere yönlendirmelerine olanak tanır.


**Standart Cikti:**

Terminalde calistirdigimiz komutlar eger bir cikti vereceklerse bunu biz yonlendirmedigimiz surece varsayilan olarak standart ciktiya yazdirmaktadir. Fakat bu durumu ">" ve ">>" yonlendirme araclari ile degistirebiliriz. 

Ornegin:

```bash
[emreakdik@dell Desktop]$ ls > file.txt
```
Yukaridaki komut her calistiginda file.txt uzerine baslangictan itibaren tekrar cikti verilir. Yani eski ciktilar tutulmaz. 

Eger eski ciktinin saklanmasini, yeni ciktinin devamine eklenmesini istiyorsak ">>" yonlendirmesini kullanmamiz gerekir.
```bash
[emreakdik@dell Desktop]$ ls >> file.txt
```

**Standart Girdi:**

Terminaldeki komutlarin cikti verebileceginden bahsetmistik ayni zamanda bir cok komut cikti verdigi gibi girdide almaktadir. Bu girdileri istersek arguman olarakta verebiliriz, istersek standart girdiyi bir dosyaya da yonlendirebiliriz. 

```bash
[emreakdik@dell Desktop]$ echo < file.txt
```

Yukarida ogrendigimiz iki yontemi tek bir komut icerisinde kullanalim:

```bash
[emreakdik@dell Desktop]$ sort < file_list.txt > sorted_file_list.txt
```

Yukaridaki komutta file_list.txt dosyasi siralanir ve siralanmis versiyonu sorted_file_list.txt dosyasina cikti olarak verilir.

### Pipelines

Pipe ("|") kullanimi ile komutlarin ciktilarini birbirinin girdisine baglayabiliriz. 

Ornek: 
```bash
[emreakdik@dell Desktop]$ ls | head -n 2
```

Yukaridaki komutta ls komutunun ciktisi head komutunun girdisine yonlendirilir ve bulundugumuz konumdaki listelenen dosya ve klasorlerin sadece ilk ikisi cikti olarak verilir.

### Genisletme (Expansion)

Terminaldeki cevre degiskenlerinden bahsedebilmistik. Eger biz bir degisken olusturduysak veya varolan bir degisken uzerinden islem yapacaksak bu degiskenlere "$" isareti ile birlikte erisebiliriz. 

Ornegin:
```bash
[emreakdik@dell Desktop]$ echo $PATH
```

Yukaridaki komut kullanildiginda terminal bizim icin cevre degiskenlerini tarar ve PATH adinda bir degisken varsa o degiskenin icerigini $PATH kullaniminin yerine yerlestirir ve komutu o sekilde calistirir.

### Komutlarda Relative ve Absolute

Yukarida relative ve absolute path yontemlerinden bahsetmistim. Ayni sekilde terminalin calisma mantiginda kullandigimiz komutlar PATH degiskeninde belirtilen dizinlerde aranip, bulunursa calistirildigi icin ayni yontem komutlari calistirirkende gecerlidir. 

Relative ornegi:

```bash
[emreakdik@dell Desktop]$ ls
```

Absolute Ornegi:
```bash
[emreakdik@dell Desktop]$ /bin/ls
```
Terminal yukaridaki iki kullanim seklinide anlar ve ls komutunu calistirir.


----

 Siradaki Eklenecek basliklar 
 - [ ] Tirnak isaretlerinin calismasi 
 - [ ] Birkomut nasil calisir (process vs) 
 - [ ]  Bir terminal Nasil calisir (lexer - parser - executer)
 - [ ] Projedeki izinli fonksiyonlar
 - [ ] CTRL-C ve CTRL-D Durumlari
