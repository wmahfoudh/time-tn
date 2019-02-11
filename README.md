# time-tn : الوقت بالتونسي
La bonne vieille manière de dire l'heure *en Tunisien*

![0105](./binaries/0105.png "ماضي ساعة و درج ما حررش")

![0450](./binaries/0450.png "الخمسة غير درجين خارج")

![0915](./binaries/0915.png "التسعة و ربع خارج")

![1155](./binaries/1155.png "الأول غير درج")

## Introduction
Le Tunisien est un mélange d’Arabe, Berbère, Français, Italien, etc. à dominante Arabe. Les tunisiens ont une manière singulière d’exprimer l’heure. Ce projet vise à décrire, documenter et implémenter cette manière pour la rendre plus accessible

## Les règles pour les heures
Chaque heure a un terme spécifique pas forcément celui du nombre qu’elle représente, ce qui suit s'applique
-	Midi = الأول (traduction = le premier)
-	Minuit = نص الليل (le milieu de la nuit)
-	1 heure = ماضي ساعة (le « passé » d’une heure)
-	2 heures = الساعتين deux heures
-	3 heures = ماضي تلاثة (le « passé » de trois heures) ou التلاثة (trois heures)
-	4 heures = الأربعة (quatre heures)
-	5 heures = الخمسة (cinq heures)
-	6 heures = الستة (six heures)
-	7 heures = السبعة (sept heures)
-	8 heures = الثمنية (huit heures)
-	9 heures = التسعة (neuf heures)
-	10 heures = العشرة (dix heures)
-	11 heures = الحداش (onze heures)
-	A part midi et minuit, l’heure du soir est exprimée de la même manière que l’heure du matin

## Les règles pour les minutes
Les minutes n’ont pas leur place, l’unité est le **DRAJ** qui vaut 5 minutes

De 5 à 35 minutes on dit l’heure **h** et on ajoute **و (et)** suivi du nombre de **DRAJ** selon ce qui suit
-	5 minutes = درج DRAJ
-	10 minutes = درجين DARJIN
-	15 minutes = ربع RBO3 (mot qui veut dire un quart d’heure)
-	20 minutes = أربعة ARB3A (quatre en Arabe)
-	25 minutes = خمسة KHAMSA (cinq en Arabe)
-	30 minutes = ستة SETTA (six en Arabe)
-	35 minutes = سبعة SAB3A (sept en Arabe)

De 40 à 55 minutes, on dit l’heure **h+1** et on ajoute **غير (moins)** suivi du nombres de **DRAJ** selon ce qui suit
- 40 minutes = أربعة ARB3A (quatre en Arabe)
- 45 minutes = ربع RBO3 (un quart d’heure)
- 50 minutes = درجين DARJIN
-	55 minutes = درج DRAJ

## la touche finale
Pour indiquer le temps avec plus de précision, on ajoute les termes **خارج** (sortant) et **ما حررش** (pas encore arrivé). Ces termes sont ajoutés à la discrétion de celui qui lit l’heure : à part le bon sens, il n’existe pas de règles pour les utiliser

Dans l’algorithme proposé, et pour une heure exprimée en unités de 5 minutes (DRAJ)
- entre DRAJ-2:30 m:s et DRAJ-1:30 m:s ما حررش est ajouté
-	entre DRAJ-1:00 m:s et DRAJ+1:00 m:s rien n’est ajouté
-	entre DRAJ+1:00 m:s et DRAJ+2:30 m:s خارج est ajouté

## Script Python
- Linux : il faut que la police *terminal* ou *tty* supporte les caractères Arabes
- Windows : l'affichage des lettres en Arabe dans la console *cmd* ou *powershell* reste problématique, il faut déjà changer le code page en ``UTF-8`` avec ``chcp 65001`` et [trafiquer la base de registres](https://www.howtogeek.com/howto/windows-vista/stupid-geek-tricks-enable-more-fonts-for-the-windows-command-prompt/) pour changer la police de la console

## Application Windows
- La bulle est déplaçable avec la souris (bouton gauche)
- Click droit pour sortir du programme
- La police utilisée est la [Noto Kufi Arabic](https://noto-website-2.storage.googleapis.com/pkgs/NotoKufiArabic-hinted.zip)
- Il faut avoir le [.net framework](http://bfy.tw/M9pg) 4.6.1 ou supérieur installé pour utiliser l'exécutable directement
