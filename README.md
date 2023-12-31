# minishell

#### Kampusumuzdeki yeni kurallar geregi, bu minishell kodunun hic degistirilmeden ya da kendinize ozgu hale getirilmeden kullanilmasi yasak. Bu yuzden direkt kopyala/yapistir kullanimi yapmayin. 



Table of Contents
=================

* [Minishell](#minishell)
   * [Giris](#giris)
   * [Terminal](#terminal)
      * [Terminal Nedir?](#terminal-nedir)
      * [Terminal Dosya Sistemi](#terminal-dosya-sistemi)
      * [Pwd](#pwd)
      * [cd](#cd)
      * [Dizinler](#dizinler)
      * [Environment Variables](#environment-variables)
      * [Builtin Commands](#builtin-commands)
      * [Redirections](#redirection)
      * [Pipelines](#pipelines)
      * [Expansion (Genisletme)](#genisletme-expansion)
      * [Komutlarda Relative ve Absolute](#komutlarda-relative-ve-absolute)
      * [Cift Tirnak Kullanimi](#cift-tirnak)
      * [Tek Tirnak Kullanimi](#tek-tirnak)
      * [Komutlarin Paralel ve Eszamanli Calismasi](#komutların-paralel-ve-eşzamanlı-çalışması)
         * [Basarili veya Basarisiz Durumunun Sorgulanmasi](#basarili-basarisiz-durumunun-sorgulanmasi)
      * [Terminal Process Yonetimi](#terminal-process-yonetimi)
      * [Sinyaller](#sinyaller)
   * [Bir Terminal/Shell Nasil Calisir?](#bir-terminalshell-nasil-calisir)
      * [Lexer](#lexer-ayrıştırıcı)
      * [Expander](#expander-genisletici)
      * [Parser](#parser-ayrıştırıcı)
      * [Executor](#executor-calistirici)
   * [Syntax Kontrolleri](#syntax-kontrolleri)
      * [Pipe](#pipe-kontrolu)
      * [Meta Karakterler](#meta-karakter-kontrolu)
   * [XOR Operatoru](#xor-operatörü---)
   * [Fonksiyonlar](#fonksiyonlar)
      * [readline](#readline)
      * [history](#history)
      * [pipe ve fork](#pipe-ve-fork)
      * [fork ve wait](#fork--ve-wait)
      * [pipe](#pipe)
      * [access](#access)
      * [execve](#execve)
      * [dup2](#dup2)
      * [dup ve dup2](#dup-ve-dup2)
     
## Giris

Bu repo minishell projesine temiz bir baslangic yapabilmenizi, minishell projesinin parcalarini basitce anlamanizi hedeflemektedir. 

Repo hala gelistirme surecindedir.

Kod kismini takim arkadasim Deniz ile birlikte gelistirmekteyiz.

Bu projede belli sinirlamalar ile kendi shell'imizi yazacagiz. Isin kod kismina gecis yapmadan once ilk olarak terminal'in calisma mantigini ve komutlarinin nasil calistigini iyi bilmek gerekiyor. Bu projeyi yapmaya niyetlendiyseniz zaten bu zamana kadar terminalle fazlasiyla icli disli oldugunuzu dusunuyorum. Yine de baslamadan once neyin nasil calistigini bilmek iyi bir secim olacaktir.

## Terminal 

### Terminal Nedir?
---

Terminal en basitinde, shell'in calistirilabilir dosyalariyla iletisim kurmanizi saglayan bir emulatordur. Mac kullanicisiysaniz iterm, windows kullanicisiysaniz powershell, linux kullanicisiysaniz ise gnome-terminal gibi sayisiz terminal ile karsilasmissinizdir. 

### Terminal Dosya Sistemi
---
Isletim sistemleri aslinda arkaplanda tum dosyalarinizi, tum klasorlerinizi bir agac yapisinda tutar. Sizin mac'te kullandiginiz finder, windowsta kullandiginiz files gibi uygulamalar sadece bu agac yapisini daha anlasilir sekilde dolasmanizi saglarlar.

![enter image description here](https://linuxcommand.org/images/file_manager.jpg)

Terminalde ise bu agac yapisinda dolasabilmeniz icin **cd** komutunu kullanabiliriz. Oldugumuz konumu gorebilmek icin ise **pwd** komutunu kullanabiliriz. 

### pwd
---
Terminalde hazir olarak calismakta oldugumuz dizini grafiksel olarak goremiyoruz. Bu yuzden calismakta oldugumuz konumu metinsel olarak goruntuleme yoluna gitmeliyiz. Bunu da **pwd** komutu ile gerceklestirebiliriz. 
```bash
[emreakdik@dell Desktop]$ pwd
/home/Desktop
```
Neredeyse butun terminallerde ilk acilis ekraninda dizin home klasoru olarak belirlenmis durumdadir. Oldugumuz terminaldeki dosya ve klasorleri goruntulemek icin ise basitce **ls** komutunu kullanabiliriz.

### cd
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
*wikipedia*: **Çevre değişkenleri, çevresel değişkenler** ya da  **ortam değişkenleri**  (ing. environment variable),  [işletim sistemi](https://tr.wikipedia.org/wiki/%C4%B0%C5%9Fletim_sistemi "İşletim sistemi")  seviyesinde konfigüre edilebilen ve [bilgisayar işlemleri](https://tr.wikipedia.org/wiki/%C4%B0%C5%9Flem_(bilgisayar) "İşlem (bilgisayar)")  tarafından erişilebilen  [değişkenlerdir](https://tr.wikipedia.org/wiki/De%C4%9Fi%C5%9Fken "Değişken"). Çoğu kez belli programların ve dosyaların  [konumlarını](https://tr.wikipedia.org/w/index.php?title=Konum_(bilgisayar)&action=edit&redlink=1 "Konum (bilgisayar) (sayfa mevcut değil)")  (ing. path) ve birden fazla işlem tarafından kullanılabilen bilgi ve ayarları tutmak için kullanılırlar. Çoğunlukla bir karakter dizisi (ing. string) olurlar.

Ortam/çevre kelimesi ile kast edilen programın [çalıştırma ortamıdır](https://tr.wikipedia.org/wiki/%C3%87al%C4%B1%C5%9Ft%C4%B1rma_ortam%C4%B1 "Çalıştırma ortamı") (ing. run-time environment). Böylece aynı işlem farklı çalıştırma ortamlarında ekstra bir konfigürasyona gerek kalmadan çalışabilir, aynı ortamdaki farklı işlemler aynı veriye ortam değişkenleri üzerinden ulaşabilirler.

Kendi yazdigimiz shell'de ise, ayiklanan komutlar bir cevre değişkeni olan PATH degiskenindeki path'ler/yollar uzerinden calistirilabilir dosyalari bulup calistirilacaktir.

Terminalde cevre degiskenlerini gormek icin **env** komutunu kullanabiliriz. Cevre degiskenleri her terminali kapatip actigimizda tekrar varsayilan hale dondurulurler.

Ornek:
```bash
[emreakdik@dell Desktop]$ env
```

Cevre değişkenlerini programimizin baslangicinda ayristirarak bir bağlı liste oluşturursak, program boyunca rahat  ve doğru bir sekilde arama yapabiliriz.

Ilk olarak cevre değişkenlerini programımıza nasil dahil edebileceğimizden bahsetmeliyim. Cogumuz bu zamana kadar sadece 2 adet main argümanından haberdardı. Fakat bu argümanlar sadece iki tane degil. Uygulamalı bir sekilde gösterirsem su sekilde:

```c
#include <stdio.h>

int main(int ac, char **av, char **env){

	for (int i = 0; env[i]; i++)
		printf("%s", env[i]);
	
	return (0);
}
```

Yukaridaki kodu calistirirsaniz asagidaki gibi bir cikti alirsiniz:

```bash
MallocNanoZone=0
USER=emre
COMMAND_MODE=unix2003
__CFBundleIdentifier=com.microsoft.VSCode
PATH=/opt/homebrew/bin:/opt/homebrew/sbin... (bende cok path cikti kisalttim)
LOGNAME=emre
ve dahasi...
```

Yani yapmamız gereken env değişkeninde olan cevre değişkenlerini bağlı listeye islemek.

Cevre değişkenleri icin ornek bir bağlı liste yapısı:

```c
typedef  struct  s_env
{
char  *env_name;
char  *content;
struct  s_env  *next;
} t_env;
```

Yukaridaki bağlı listeyi oluşturduktan sonra, tüm cevre değişkenlerinin "=" operatöründen oncesini env_name olarak, "=" operatöründen sonraki kısmı ise content olarak ayiklayabilirsiniz.

Bu ayıklama islemlerini ise basit bağlı liste fonksiyonları ile halledebilirsiniz. Bu kısmi size bırakıyorum.

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
---
Pipe ("|") kullanimi ile komutlarin ciktilarini birbirinin girdisine baglayabiliriz. 

Ornek: 
```bash
[emreakdik@dell Desktop]$ ls | head -n 2
```

Yukaridaki komutta ls komutunun ciktisi head komutunun girdisine yonlendirilir ve bulundugumuz konumdaki listelenen dosya ve klasorlerin sadece ilk ikisi cikti olarak verilir.

### Genisletme (Expansion)
---
Terminaldeki cevre degiskenlerinden bahsedebilmistik. Eger biz bir degisken olusturduysak veya varolan bir degisken uzerinden islem yapacaksak bu degiskenlere "$" isareti ile birlikte erisebiliriz. 

Ornegin:
```bash
[emreakdik@dell Desktop]$ echo $PATH
```

Yukaridaki komut kullanildiginda terminal bizim icin cevre degiskenlerini tarar ve PATH adinda bir degisken varsa o degiskenin icerigini $PATH kullaniminin yerine yerlestirir ve komutu o sekilde calistirir.

### Komutlarda Relative ve Absolute
---
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

### Cift Tirnak
---

Çift tırnakların içine metin yerleştirirsek, kabuk tarafından kullanılan komutlar özel anlamlarını kaybeder ve bunlar sıradan karakterler olarak işlenir. İstisnalar, "$", "" (ters eğik çizgi) ve "`" (ters tırnak) karakterleridir. Bu, kelime bölme, yol adı genişletme, tilde genişletme ve süslü parantez genişletmesinin engellendiği anlamına gelir, ancak parametre genişletme, aritmetik genişletme ve komut yerine koyma hala gerçekleştirilir.

```bash
emre@emres-MacBook-Air ~ % echo "$USER $((2+2)) $(cal)"
emre 4    November 2023
Su Mo Tu We Th Fr Sa
          1  2  3  4
 5  6  7  8  9 10 11
12 13 14 15 16 17 18
19 20 21 22 23 24 25
26 27 28 29 30
```

### Tek Tirnak 
---

Tüm genişlemeleri bastırmamız gerektiğinde tek tırnak kullanırız. İşte tırnaksız, çift tırnak ve tek tırnak karşılaştırması:

```bash
emre@emres-MacBook-Air ~ % echo text ~/*.txt {a,b} $(echo foo) $((2+2)) $USER
text /home/emre/ls-output.txt a b foo 4 me 

emre@emres-MacBook-Air ~ % echo "text ~/*.txt {a,b} $(echo foo) $((2+2)) $USER"
text ~/*.txt {a,b} foo 4 me 

emre@emres-MacBook-Air ~ % echo 'text ~/*.txt {a,b} $(echo foo) $((2+2)) $USER'
text ~/*.txt {a,b} $(echo foo) $((2+2)) $USER
```


Tabii ki! İşte terminallerdeki çocuk işlem (child process) oluşturma, pipelar, redirectionlar ve komutların paralel veya eşzamanlı çalışması hakkında kapsamlı bir rehber:

---

### Komutların Paralel ve Eşzamanlı Çalışması

Birden fazla komutu paralel veya eşzamanlı olarak çalıştırmak için bazı araçlar ve yöntemler vardır:

#### `&` Operatörü (Arka Planda Çalıştırma)

Bir komutu arka planda çalıştırmak için `&` operatörünü kullanabilirsiniz.

Örnek:
```bash
emre@emres-MacBook-Air ~ % long_running_command &
```

Yukarıdaki komut, `long_running_command` komutunu arka planda çalıştırır.

#### `;` Operatörü (Sıralı Çalıştırma)

Komutları sırasıyla çalıştırmak için `;` operatörünü kullanabilirsiniz.

Örnek:
```bash
emre@emres-MacBook-Air ~ % command1 ; command2
```

Yukarıdaki komut, `command1` komutunu tamamladıktan sonra `command2` komutunu çalıştırır.

#### `|` Operatoru 

Pipe operatoru, komutların ciktilarini ve girdilerini birbirine bağlamamıza yarar demistik. Fakat bu durumda bilinenin disinda bir durum var. Pipe kullanımında komutlar es zamanli degil paralel calisirlar. **Ezamanli ve paralel farkini öğrenmek istiyorsanız philosophers repomdaki konu anlatımıma bakabilirsiniz.** 

Ornek vermek gerekirse basitçe ls ve head fonksiyonlarını pes pese kullandınız diyelim. ls komutu daha isini bitirmeden head komutuda isine baslar. Kisaca ls yazdıkça head okur yani paralel calisirlar.

Daha basitçe anlayalım:

```bash
emre@emres-MacBook-Air ~ % sleep 1 | echo "neden echo sleep komutunu beklemedi?"
neden echo sleep komutunu beklemedonce calisti?"
neden echo once calisti?
```
Yukaridaki komutu calistirirsaniz eğer sleep komutunu önce yazmamıza rağmen echo paralel calisarak ciktisini verdi. 

#### `&&` Operatörü (Başarılı Olursa Çalıştırma)

Komutları yalnızca önceki komut başarılı olduğunda çalıştırmak için `&&` operatörünü kullanabilirsiniz.

Örnek:
```bash
emre@emres-MacBook-Air ~ % command1 && command2
```

Yukarıdaki komut, `command1` komutu başarılı olursa `command2` komutunu çalıştırır.

#### `||` Operatörü (Başarısız Olursa Çalıştırma)

Komutları yalnızca önceki komut başarısız olduğunda çalıştırmak için `||` operatörünü kullanabilirsiniz.

Örnek:
```bash
emre@emres-MacBook-Air ~ % command1 || command2
```
Yukarıdaki komut, `command1` komutu başarısız olursa `command2` komutunu çalıştırır.

#### Basarili Basarisiz Durumunun Sorgulanmasi

Komutlar basarili sekilde calisirlarsa exit code olarak 0 döndürürler. Eğer bir komut yanlış calistiysa 0 disinda bir exit code dondurur, bu da hatasının cikis kodunu verir.

Peki ya son calisan komut'un return degerini nasıl kontrol ederiz? Orneklerle bakmak gerekirse:

```bash
emre@emres-MacBook-Air ~ % echo emre
emre
emre@emres-MacBook-Air ~ % echo $?
0
```
ya da
```bash
emre@emres-MacBook-Air ~ % ls mre
ls: mre: No such file or directory
emre@emres-MacBook-Air ~ % echo $?
1
```

Yukarida görüldüğü gibi "$?" kullanımı son calisan islemin cikis kodunu ulaşılabilir kilar.

### Terminal Process Yonetimi
---
Terminala yazdigimiz komutlar genel olarak child process oluşturularak calistirilirlar. Istisnai olarak built-in komutlar'in calisma mantiklarindan kaynakli child process'e ihtiyaci olmaz. 

Bir "child process" (çocuk işlem) oluşturulur ve komut bu process içinde çalıştırılır. Bu, çeşitli avantajlar sunar. Örneğin, paralellik sağlar, böylece birden fazla komut aynı anda çalıştırılabilir ve bir komut diğerleriyle etkileşime girebilir. Ayrıca, bir işlem hata verdiğinde veya çöktüğünde ana terminal işlemi etkilenmez.

Eger calistirilan komut, child process olusturarak calistirilmasaydi, komut bitince veya sinyal ile islemi durdurdugumuzda terminalin kendisi kapanirdi. 

Bunu uygulamalı sekilde gösterebilmek icin **exec** komutundan bahsedeceğim. **exec** komutu ile calistirdigimiz komutlar, Child processes oluşturmak yerine ana processte calisir ve bittiklerinde ana process kapandigi icin terminalimiz kapanır. 

Ornegin:

```bash
emre@emres-MacBook-Air ~ % exec ls
```

Yukaridaki komutu calistirdigimizda ls komutu calisir ve biz daha ciktiyi göremeden terminal kapanır. Komutun calyistiginin kantini ise asagidaki gibi elde edebilirsiniz.

```bash
emre@emres-MacBook-Air ~ % exec ls > output.txt
```

Process nedir? Thread Nedir? gibi soruların cevaplarını philosophers repomda bulabilirsiniz. Process oluşturma gibi işlevlere yarayan fonksiyonları yazının devamında goreceksiniz.

### Sinyaller
---
Shellimizde CTRL + C, CTRL + D gibi tus kombinasyonlarının yönetimini yapacağız. Bunun icin ise kodumuza sinyal yönetimini islememiz gerekecek.

CTRL + C kombinasyonu programımıza SIGINT sinyalini gönderir. Bu sinyal ile birlikte hali hazırda calismakta olan islemin durdurulmasını saglar. Ornek bir kod ile incelersek daha iyi anlasilacagini düşünüyorum:

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int signum) {
    printf("CTRL-C received, exiting...\n");
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler); // SIGINT sinyalini işleyen fonksiyon
    while (1) {
        // Shell mantığı burada
    }
    return 0;

// void (*signal(int signum, void (*handler)(int)))(int);
// signum = kaydedilecek sinyalin numarasını belirtir. Yani,
// hangi sinyalin işlenmesini istediysek onu belirten bir tamsayı.
// Örneğin Ctrl+C gönderdiği 'SIGINT' sinyali için nu değer '2' olacak.
// handler = belirtilen sinyalin işlenmesi için atanacak olan işlevi taşıyan işaretçidir.
// Yani, bir sinyal alındığında çağırılacak olan işlevi belirtir.
// bu işlev int tipinde parametre alır ve void tipinde değer döndürür.
// signal = Bu, sinyal fonksiyonunun dönüş değeridir. 
// fakat signal fonksiyonu sigaction kadar güvenilir değildir.

}
```
CTRL + D kombinasyonu ise, shellin girdi almasını durdurur. Basitçe shell'i kapatır. Bunun icin ise SIGQUIT sinyalini kullanır. Yine üstte gösterilen ornek uzerinden SIQQUIT sinyali icin bir calışma yapılabilir.

## Bir Terminal/Shell Nasil Calisir?

Bu başlıkta basitçe, shell'in calışma adımlarından bahsedeceğim. Shell aslında basitçe bir sinirsiz döngüden ibarettir. Kullanıcıdan girdi bekler, girdiyi alir, parcalar, genişletir, birleştirir ve calistirir. Bu dongunun adımları basitçe asagidaki gibidir:

1. Kullanicidan girdi bekler
2. Girdiyi parselar/ayristirir
3. Komutu calistirir ve sonucu verir
4. Ilk adima geri doner 

Ikinci ve ucuncu adımları daha derinmelesine incelemeye kalktigimizda 4 adim oldugunu goruruz. Bunlar ise: `lexer` → `expander` → `parser` → `executor`

![](https://user-images.githubusercontent.com/68693691/193665518-0c0c7fec-38a9-4f6c-91ca-fef606abfb0d.png) 
Yukaridaki goruntuyu maiadegraaf isimli kullanıcıdan aldim. 

Simdi aşamaları basitçe aciklamak istiyorum.

 ### Lexer (Ayrıştırıcı)
   Lexer aşaması, kullanıcının girdiğini alır ve bu girdiyi belirli öğelere, yani "token"lara böler. Bir token, girdinin birimlerini temsil eder. Örneğin, bir token bir komut, bir değişken adı, bir operatör veya bir sayı olabilir. 

Lexer asamasi icin genel olarak bir bağlı liste oluşturulur ve bu bağlı listede ayristirilmis tokenler bulunur. Ornek bir yapı olarak sunu gösterebilirim:

```c
typedef  struct  s_lexlist
{
char  type;
char  *content;
struct  s_lexlist  *next;
} t_lexlist;
```

Yukaridaki gördüğünüz bağlı liste yapısındaki bir kolaylıktan bahsedeceğim. Komut satirimizi tokenlara böldükten sonra bu gördüğünüz bağlı liste yapısında **content** değişkenine tokenleri isliyoruz.

Peki ya **type** degiskeni nedir? diyorsanız aslında type değişkeni  **content** değişkeninin içerisine oturttugumuz tokenin tipini tutar. Bunun sayesinde programimizin ilerleyen kisimlarinda tekrar tekrar tokenlerin icini analiz etmemize gerek kalmayacak ve type uzerinden kontrol sağlayabileceğiz (örneğin, syntax kontrolu). 

### Expander (Genisletici)
   Expander aşaması, bazı terminal komutlarının veya ifadelerinin genişlemesini saglar. Özellikle, değişkenlerin ve özel karakterlerin değerlerini ve işlevlerini yerine getirir. Örneğin, $USER kullaniminda cevre degiskenlerinden USER degiskeninin karsiligini bulur ve yerine karsiligini koyar.

   !! Genisletme isleminde tek tirnak ve cift tirnak kullanimlarina dikkat edilmesi gerekir. Tek tirnak ve cift tirnak kullanimlarini yukaridaki aciklamalarimda bulabilirsiniz. Bu yuzden bir değişkeni veya işareti genisletmeden once, tek tirnak icerisinde mi kontrol edilmesi gerekir. 

Genisletme esnasında, cevre değişkenleri disinda genişletmelerinde yapılması gerekir. Bunlar:

- **$?:** Bir önceki komutun cikis degerine ulasilmasini saglar. Terminal komutları basari durumunda 0, basarisizlik durumunda ise 0'dan büyük olmak uzere hata kodunu dondururlar.

- **$$:** Calistirildigi processin pid'sine ulasilmasini saglar.  

- **~:** Tilde isareti ise kullanicinin Home yolunu temsil eder.

- **$:** Sonrasinda yazılan değişken ismi cevre değişkenlerinden bulunur ve yerine koyulur. Genel olarak  $USER gibi bir kullanım olsa da ${USER} kullanımı da ayni sekilde calismaktadir. Bunun Disinda dolar kullanımında $"USER" ya da $'USER' kullanimlarindaki degisiklikler de göz önünde bulundurulmalıdır. 

> Eger unuttuklarım varsa daha sonra ekleyeceğim.

### Parser (Ayrıştırıcı)
Parser, lexer tarafından oluşturulan tokenları alır ve bu tokenları bir sözdizimi ağacına çevirir. Sözdizimi ağacı, komutların yapısını ve ilişkilerini temsil eder. Örneğin, bir komutun bir argümanı veya seçeneği olabilir, ve bu ağaç bu ilişkiyi gösterir. Parser, kullanıcının girdisinin doğru bir şekilde yapılandırıldığından emin olur. Eğer girdi doğru bir sözdizimi yapısına sahip değilse, parser hata verir.

### Executor (Calistirici)
Executor, sözdizimi ağacını alır ve bu ağacı yorumlayarak komutları gerçek dünyada yürütür. Yürütücü, kullanıcı komutlarını işletim sistemine veya diğer programlara iletir ve sonuçları kullanıcıya sunar. Örneğin, bir "ls" komutunu yürütmek, dizin içeriğini listeler ve sonucu ekrana yazdırır.

## Syntax Kontrolleri

Terminalimizin doğru bir sekilde calisabilmesi icin bazı syntax kontrollerini yapmamız gerekiyor. Bu kontroller daha çok meta karakterler ve pipe etrafında dönmektedir. Bu noktada kendimizce kullandigimiz kontrolleri ornek olması amaçlı anlatacağım. 

Syntax kontrolunu insanlar genel olarak lexer aşamasında gerçekleştirmekteler. Lexer'da tüm kelimelerin , meta karakterlerin token'a dönüştürülerek bir bağlı liste yapısına işlendiğinden bahsetmiştim. 

Kucuk obeklere yani tokenlere ayrilmis olan komut satirimiz uzerinden syntax kontrol edilebilir. Ornegin bağlı listenin ilk node'unda pipe varsa bu syntax hatasıdır ve bir kaç ufak kontrolle bunu yakalayabiliriz.

### Pipe Kontrolu

- Pipe'in islev gereği komut satirinin baslangicinda olmaması gerekir. 
- Pipe'in işlev gereği yan yana olmamalıdır.
- Pipe sonrasında bir metin tokeni olması gerekmektedir.

!! Pipe sonrasinda bir girdi yoksa, yani sonda pipe varsa, kodunuzun bu kisimda da terminal gibi davranmasi gerekir. 
	Ornegin "cat |" komutunu terminalinize yazarsaniz, terminalin bir girdi istedigini gorursunuz. Yani eksik komut veya argumani terminal tamamlamaktadir.

### Meta Karakter Kontrolu

- Meta karakterlerin sonrasında text olmak zorundadır. Bu noktada meta karakterden sonra text olması kontrolu yetecektir. 

- Yani meta karakterden sonra text yoksa veya null varsa meta karakter kullanımında bir syntax hatası olduğu anlamına gelir.

## XOR Operatörü ( ^ )

XOR operatoru **Exclusive OR** operatoru olarak bilinir. Veya operatoruyle benzer islere yarar fakat farkliliklar mevcuttur. 

Veya operatoru karsilastirdigimiz taraflardan herhangi biri 1 oldugu taktirde 1 sonucunu verir ve bu iki tarafinda 1 oldugu durumdada gecerlidir.

Fakat XOR operatoru ile bu durum bu sekilde degildir. Xor operatoru ile sadece "iki taraftan biri" 1 oldugu taktirde 1 sonucunu verir. Yani iki tarafinda ayni oldugu durumlarda 1 sonucunu vermez.

Asagidaki tabloda durumlar daha iyi anlasilabilir:

| p | q | p^q | 
|--|--|--|
| 1 | 1 | 0 |
| 1 | 0 | 1 | 
| 0 | 0 | 0 |
| 0 | 1 | 1 |

## Fonksiyonlar


### readline

```c
#include  <stdio.h>
#include  <stdlib.h>
#include  <readline/history.h>
#include  <readline/readline.h>

int  main(void)
{
	char  *str;

	// system("clear");
	str  =  readline("minishell> ");

	/*
	terminalden okur ve okudugunu return eder, terminalde prompt gosterir.
	prompt null veya bos string ise prompt gosterilmez.
	
	return edilen satir malloc ile alloclanmistir yani serbest birakilmalidir.
	satirin sonundaki new line silinerek return edilir.
	
	eger okunan satirin sonuna gelindiyse yani EOF ile karsilasildiysa ve
	satir bos ise null dondurur.
	eger bos olmayan bir satir EOF ile bitmisse, eof'a newline olarak davranilir.
	*/
	add_history(str);
	printf("%s\n", str);

	free(str);
	return  (0);
}
```

### history

```c
#include  <stdio.h>
#include  <readline/history.h>
#include  <readline/readline.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <fcntl.h>

int  ft_strcmp(char  *str, char  *dst){

	int  i  =  0;

	while (dst[i]){
	if (str[i] !=  dst[i])
	break;
	i++;
	}
	return  str[i] -  dst[i];
}

void  exec_history(char  *history_path){

	int  i  =  0;
	int  fd;
	int  rd;
	char  c;

	fd  =  open("emre.txt", O_RDWR);
	while((rd  =  read(fd, &c, 1)) !=  0)
		write(1, &c, 1);
}

int  main(int  ac, char  **av, char  **envp){

	char  *str;
	char  *history_path  =  "emre.txt";

	while (1){
	str  =  readline("minishell> ");
	add_history(str);
	/*
	void add_history (const char *string);

	arguman olarak girilen string'i gecmis'e ekler.
	fakat bu gecmis anlik olarak o process'te tutulan gecmistir.
	yani program bittikten sonra history komutu ile o gecmis gorulemez.
	*/
	write_history(history_path);
	/*
	bu fonksiyon minishell'de kullanilabilir durumda degil.

	fonksiyon verilen stringde bir dosya olusturur ve bu dosyaya 
	add_history ile eklenmis olan gecmis'i yazar.
	*/
	if (!strcmp(str, "history"))
	exec_history(history_path);
	if (!strcmp(str, "exit"))
	break;
	}
	free(str);
}
```

### pipe() ve fork()

```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int pipe_fd[2];
    char buffer[100];

    pipe(pipe_fd);
    pid_t child_pid = fork();

    if(child_pid == 0)
    {
        // Child process
        close(pipe_fd[1]); // closed write end
        read(pipe_fd[0], buffer, sizeof(buffer)); 
        printf("Child Process Write: %s\n", buffer);
        close(pipe_fd[0]);
    }
    else
    {
        // Parent process
        close(pipe_fd[0]); // closed read end
        write(pipe_fd[1], "Pipe", 4);
        close(pipe_fd[1]);
    }
    return (0);
}

// pid_t fork(void);
// fork fonksiyonu process oluşturmak için kullanılır. Bu fonksiyon çağrıldığında,
// mevcut sürecin tam kopyasını oluşturur. Böylece program 2 farklı yoldan devam eder.
// biri parent process diğeri ise child process olarak adlandırılır.
// her iki süreç de aynı kodu paylaşur fakat ayrı bellek alanlarına sahiptirler.

// int pipe(int pipefd[2]);
// pipefd[2] = iki elemanlı bir dizi alır. Bu dizi, birinci eleman yazma ucunu (write end) ve
// ikinci eleman okuma ucunu (read end) temsil eder.
// pipe fonksiyonu, iki süreç arasında iletişim kurmak için kullanılan bir iletişim kanalı oluşturur. 
// bu iletişim kanalı bir süreçten diğerine veri iletilmesini sağlar.

```

### fork () ve wait()

```c
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int ac, char **av){

    int pid = fork();
    /*
    fork cagirildigi process'i kopyalayarak yeni bir process olusturur.
    yeni olusturulan process child process olarak adlandirilir.
    fork fonksiyonunun cagirildigi process'e ise parent process denir.

    parent process ve child process ayri bellek alanlarina sahiptir.
    ama yine de ayrildiklarinda ayni icerige sahiptirler.
    processlerin bellek alanlarina yazmalari esnasinda birbirlerini etkilemezler.

    child process kendine has process ID'ye sahiptir.

    basari durumunda parent process'te child process'in PID'sini return eder, 
    child process'te ise 0 return eder.
    */
    int status;
    int gpid;
    if (pid > 0){ // parent process icin kod blogu
        gpid = wait(&status); // child processin bitmesini bekler
        /*
        pid_t wait(int *wstatus);

            wait fonksiyonu herhangi child processin durumunu kontrol eder.
            child process'te bir degisiklik olana kadar bekler ve sonlanmaz.
            return olarak biten child processin id'sini dondurur
            status degiskeni ise child processin bitme durumunu tutar
            hata durumunda -1 dondurur.
        */
        printf("parent process: \n\n");
        printf("parent process fork() return: %d\n", pid);
        printf("sonlanan child process id: %d\n", gpid);
        printf("parent process blogundan child processin bitme durumu: %d\n", status);
        printf("bitme durumu beklediginden garip dondu degil mi? :)\n");
    }
    else if (pid == 0){ // child process icin kod blogu
        printf("child process: \n\n");
        printf("child process fork() return: %d\n", pid); 
        /* 
        Child process de pid degiskeni 0 tutar cunku fork fonksiyonu child 
        processte 0 dondurur fakat parent process de child processin id'sin
        dondurur
        */
        printf("child processin id: %d\n", getpid());
        printf("child processin hangi parent process'e ait oldugu id: %d\n\n", getppid()); 
        // fark ettiysen getpid degil getppid :)
    }
    else // fork fonksiyonunun basarisiz olmasi durumu
        printf("fork error\n");
    return 3; // wait fonksiyonunun return'u icin 3 yaptim
}

```
### pipe()

```c
#include <unistd.h>
/*
fork, pipe, read ve write fonksiyonlari icin gerekli unistd
*/
#include <sys/wait.h>
/*
wait fonksiyonu icin gerekli sys/wait
*/
#include <stdio.h>

int main(void){
    int fd[2]; // pipe icin iki dosya tanimlayacagiz

    pipe(fd); // pipe fonksiyonu ile fdleri olusturuyoruz
    /*
    int pipe(int pipefd[2]);
    fd[0] -> read icin
    fd[1] -> write icin

    write fd'sine yazildiktan sonra kernel write fd'sini read fd'sinden okunana 
    kadar saklar.

    basari durumunda 0 dondurur. hata durumunda -1 dondurur.
    */
    int pid = fork(); // iki process arasinda pipelayacagimiz icin fork ile child 
    // process olusturuyoruz

    if (pid > 0){ // parent process icin kod blogu
        close(fd[0]);
        /*
        parent process ile birlikte sadece yazma islemi yapacagimiz icin okuma 
        fd'sini kapatiyoruz.        
        */
        write(fd[1], "hello", 5);
        close(fd[1]);
        /*
        kapatilan fd sadece oldugu process icin kapatiliyor. child process 
        olusturuldugunda parent process'in tum bellek alanini
        kendi alanina kopyaladigi icin diger processte kapatilmis olan fd diger bir 
        processte miras kalarak yasamina devam edebiliyor.
        */
    }
    else if (pid == 0){
        close(fd[1]); // yazma islemi yapilmayacagi icin yazma fd'sini kapatiyoruz
        char buf[5]; // okuma islemi icin bir buffer olusturuyoruz
        read(fd[0], buf, 5); // pipe'dan okuma islemi gerceklestiriyoruz
        printf("%s\n", buf); // okunan degeri ekrana yazdiriyoruz
        close(fd[0]); // okuma islemi bittigi icin okuma fd'sini kapatiyoruz
    }
    else
        printf("fork error\n");
    return 0;
}
```

### access()

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // budur

int main() {
    const char* file = "example.txt";

    if (access(file, F_OK) == 0) {
        printf("'%s' dosyası mevcut.\n", file);

        if (access(file, R_OK) == 0) {
            printf("'%s' dosyası okunabilir.\n", file);
        } else {
            printf("'%s' dosyası okunabilir değil.\n", file);
        }

        if (access(file, W_OK) == 0) {
            printf("'%s' dosyası yazılabilir.\n", file);
        } else {
            printf("'%s' dosyası yazılabilir değil.\n", file);
        }
    } else {
        printf("'%s' dosyası mevcut değil.\n", file);
    }

    return 0;
}

/*
int access(const char *pathname, int mode);

fonksiyon, erisilen fonksiyona olan izinlerimizi veya dosyanin varligini kontrol eder.
*/
```

### execve()

```c
#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {

    /*
    envp degiskeni exec fonksiyonlarinin calismasi icin gereken sistem ortam 
    degiskenlerini tutar.

    bu string'in sonunda null vardir.

    bu stringdeki degiskenlerin formu ise name=value'dur.

    ornekler;

    user, giris yapilan kullanicinin ismidir
    home, kullanicinin home dizinidir
    path,  "sh(1)" ve birçok diğer programın, eksik bir yol adıyla bilinen bir 
    dosyayı ararken uyguladığı dizin önekleri dizisi. Bu önekler ':' ile ayrılır. 
    pwd, bulunulan calisma dizinini gosterir
    shell, kullanicinin login shell'inin yoludur
    term, hangi tip terminal oldugunu tutar
    */

    char *args1[] = {"/bin/ls", "-l", NULL};
    char *args2[] = {"/usr/bin/wc", "-l", NULL};
    int pid;
    int fd[2];

    if (pipe(fd) == -1)
        perror("pipe");
    pid = fork();

    if (pid == 0)
        execve(args1[0], args1, envp);
    else if (pid > 0){
        
    }
    else
        perror("fork");

    execve(args1[0], args1, envp);
    /*
    int execve(const char *pathname, char *const argv[],
                  char *const envp[]);
    lokasyonu belirtilen programi calistirir. calistirilan
    program var olan bellek alaniyla birlikte baslar fakat yeni baslangic
    degerleriyle birlikte tamamen yeni bir program olarak calisir.
    cagirildigi program sonlandirilir.
    
    lokasyonda calistirilabilir binary veya #!interpreter ile baslayan
    bir script olmalidir.

    execve() basari durumunda return etmez, yeni program eski programdaki
    text, initialized data, uninitialized data ve stack alanlarinin uzerine yazar.

    program ptraced ise, basarili calisitrmadan sonra SIGTRAP sinyali gonderilir.

    hata durumunda -1 dondurur.
      */
    execve(args2[0], args2, envp);
    return 0;
}

```

### dup2()

```c
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void child_process(int fd[], char *args[]){
    close(fd[0]); // child process ile okuma gerceklestirmeyecegim icin pipe'in (boru'nun :)) okuma tarafini kapatiyorum
    dup2(fd[1], STDOUT_FILENO); 
    /*
    int dup2(int oldfd, int newfd)

    oldfd yerine newfd yerlestirilir ve newfd eger onceden acilmissa yeniden 
    kullanilmadan once sessizce kapatilir.

    eger oldfd gecerli bir fd degilse, fonksiyon basarisiz olur ve newfd 
    kapatilmaz.

    eger oldfd gecerliyse ve newfd ile ayni degere sahipse, dup2 hicbir sey yapmaz 
    ve newfd'yi return eder.

    basari halinda fonksiyon newfd'yi return eder. error durumunda -1 return eder.
    */
    close(fd[1]); // pipe'in yazma kismini kapatiyorum cunku artik o kisma standart 
    // cikti uzerinden erisecegim
    execve(args[0], args, NULL); // ls -l komutunu calistiriyorum
}

void parent_process(int fd[], char *args[]){
    waitpid(-1, NULL, 0);
    /*
    ikinci komutun calistirilmasi icin ilk komutun bittiginden emin olmamiz 
    gerekiyor. bu yuzden ilk komutu child process
    ile gerceklestirdim ki waitpid fonksiyonu ile child process'in yani ilk komutun 
    bitmesini bekleyebiliyim. 
    */
    close(fd[1]); // parent process ile yazma gerceklestirmeyecegim icin pipe'in 
    // (boru'nun :)) yazma tarafini kapatiyorum
    dup2(fd[0], STDIN_FILENO); // pipe'in okuma kismini stdin'e yonlendiriyorum
    close(fd[0]); // pipe'in okuma kismini kapatiyorum cunku artik o kisma standart 
    // girdi uzerinden erisecegim
    execve(args[0], args, NULL); // wc -l komutunu calistiriyorum
}

int main(void){

    char *args[] = {"/bin/ls", "-l", NULL}; // calistirilacak komut 1
    char *args2[] = {"/usr/bin/wc", "-l", NULL}; // calistirilacak komut 2
    int fd[2]; // pipe icin dosya tanimlayicisi
    int pid;  // fork fonksiyonunun donus degeri

    if (pipe(fd) == -1) // pipe olusturulmasi
        perror("pipe");
    pid = fork(); // fork fonksiyonunun cagrilmasi
    if (pid == 0) // child process icin kod blogu
        child_process(fd, args);
    else if (pid > 0) // parent process icin kod blogu
        parent_process(fd, args2);
    else
        perror("fork");
    
    return 0;
}
```

### dup() ve dup2()

```c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    // Dosya tanımlayıcıları
    int dosya1, dosya2;

    // Bir dosya aç
    dosya1 = open("dosya1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dosya1 == -1)
    {
        perror("dosya1 açma hatası");
        return 1;
    }

    // stdout dosya tanımlayıcısını dosya1 ile aynı yap
    dosya2 = dup2(dosya1, 1);
    if (dosya2 == -1)
    {
        perror("dup2 hatası");
            return 1;
    }

    // Yeni stdout'a yazdır
    printf("Bu çıktı dosya1.txt'ye yönlendirildi.\n");

    // Dosyaları kapat
    close(dosya1);

    return 0;
}

// int dup2(int oldfd, int newfd);
// oldfd = kopyalanacak olan dosya.
// newfd "oldfd"nin kopyalacağı yeni dosya.
// dup2() fonksiyonu bir sistem çağrısıdır ve iki dosya arasında bir bağlantı kurar.
// Genel olarak işlevi bir dosyanın içeriğini başka dosyaya kopyalamaktır.
// Dosyalar arasında yönlendirme yapmak için kullanılır.
// Eğer newfd mevcutsa kapatılır. Yani close(newfd) çağrısı yapılır.
// oldfd newfd'ye atanır.
// bu işlemler sonucunda, newfd artık oldfd ile aynı dosyayı gösterir.

// dup() ve dup2() farkları..
// dup() fonksiyonu yalnızca bir dosya tanımlayıcısı (oldfd) alır ve
// bu tanımlayıcıyı kullanarak mevcut olarak açık olan bir dosyayı kopyalar.
// dup2() fonksiyonu ise iki dosya tanımlayıcısı (oldfd ve newfd) alır.
// oldfd7yi kullanarak mevut olarak açık olan dosyayı, newfd'ye kopyalar. Eğer
// newfd zaten açıksa, önce onu kapatır ve ardından kopyalama işlemini gerçekleştirir.

```
---

 Siradaki Eklenecek basliklar 
 - [x] Tirnak isaretlerinin calismasi 
 - [x] Bir komut nasil calisir (process vs) 
 - [ ]  Bir terminal Nasil calisir (lexer - parser - executer)
 - [ ] Projedeki izinli fonksiyonlar
 - [ ] Sinyaller Hakkinda Derinlemesine Aciklama
 - [ ] Builtin Commands Kod Senaryolari
 - [ ] Syntax Kontrolu Nasil Yapilir?

