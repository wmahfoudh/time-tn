# time-tn : الوقت بالتونسي
La bonne vieille manière de dire l'heure *en Tunisien*

![0105](./binaries/0105.png "ماضي ساعة و درج ما حررش")

![0450](./binaries/0450.png "الخمسة غير درجين خارج")

![0915](./binaries/0915.png "التسعة و ربع خارج")

![1155](./binaries/1155.png "الأول غير درج")

## Intro 
Les tunisiens ont une manière particulière d’exprimer l’heure dont certaines subtilités disparaissent peu à peu.  Le Tunisien est un mélange d’Arabe, Berbère, Français, Italien, etc.

Voici les règles générales pour dire l’heure en Tunisien :
1.	Les minutes n’ont pas leur place pour dire l’heure
2.	L’unité est le « DRAJ » qui vaut 5 minutes
3.	De 5 à 35 minutes on exprime l’heure **h** et on dit **و (et)** suivi du nombre de « DRAJ » (lignes qui suivent de 5 à 11)
4.	De 40 à 55  minutes, on exprime l’heure **h+1** et on dit **غير (moins)** suivi du nombres de « DRAJ » (lignes 12 à 15)
5.	5 minutes = درج DRAJ
6.	10 minutes = درجين DARJIN
7.	15 minutes =  ربعRBO3 (mot qui veut dire un quart d’heure)
8.	20 minutes = أربعة ARB3A (quatre en Arabe)
9.	25 minutes = خمسة KHAMSA (cinq en Arabe)
10.	30 minutes = ستة SETTA (six en Arabe)
11.	35 minutes = سبعة SAB3A (sept en Arabe)
12.	40 minutes = أربعة ARB3A (quatre en Arabe)
13.	45 minutes = ربع RBO3 (un quart d’heure)
14.	50 minutes = درجين DARJIN
15.	55 minutes = درج DRAJ
16.	Chaque heure a un terme spécifique pas forcément celui du nombre qu’elle représente
17.	Midi = الأول (traduction = le premier)
18.	Minuit = نص الليل (le milieu de la nuit)
19.	1 heure = ماضي ساعة (le « passé » d’une heure)
20.	2 heures = الساعتين deux heures
21.	3 heures = ماضي تلاثة (le « passé » de trois heures) ou التلاثة (trois heures)
22.	4 heures = الأربعة (quatre heures)
23.	5 heures = الخمسة (cinq heures)
24.	6 heures = الستة (six heures)
25.	7 heures = السبعة (sept heures)
26.	8 heures = الثمنية (huit heures)
27.	9 heures = التسعة (neuf heures)
28.	10 heures = العشرة (dix heures)
29.	11 heures = الحداش (onze heures)
30.	A part midi et minuit, l’heure du soir est exprimée de la même manier que l’heure du matin
31.	Pour indiquer le temps avec plus de précision, on ajoute à ce qui précède les termes **خارج** (sortant) et **ما حررش** (pas encore arrivé)
32.	 **خارج** (sortant) et **ما حررش** sont ajoutés au pif (au vu de celui qui lit l’heure), à part le bon sens, il n’existe pas de règle pour les utiliser
33.	*Dans le programme proposé, et pour un DRAJ donné*, entre -2:30 m:s et -1:30 m:s ما حررش est ajouté
34.	*Dans le programme proposé, et pour un DRAJ donné*, entre -1:00 m:s et +1:00 m:s ; rien n’est ajouté
35.	*Dans le programme proposé, et pour un DRAJ donné*, entre +1:00 m:s et +2:30 m:s خارج est ajouté

Ce projet vise à documenter cette manière et de l’implémenter dans divers langages de programmation.

## Script Python
- Linux : il faut que la police *terminal* ou *tty* supporte les caractères Arabes
- Windows : l'affichage des lettres en Arabe dans la console *cmd* ou *powershell* reste problématique, il faut déjà changer le code page en ``UTF-8`` avec ``chcp 65001`` et [trafiquer la base de registres](https://www.howtogeek.com/howto/windows-vista/stupid-geek-tricks-enable-more-fonts-for-the-windows-command-prompt/) pour changer la police de la console

## Application Windows
- La bulle est déplaçable avec la souris (bouton gauche)
- Click droit pour sortir du programme
- La police utilisée est la [Noto Kufi Arabic](https://noto-website-2.storage.googleapis.com/pkgs/NotoKufiArabic-hinted.zip)
- Il faut avoir le [.net framework](http://bfy.tw/M9pg) 4.6.1 ou supérieur installé pour utiliser l'exécutable directement
