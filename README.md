# Epitière de Janvier 2021 à Juin 2021

|	Dossier Data :
|		- Logo du groupe Epitière
|
|	Dossier Documents :
|		- Cahier des charges de notre projet
|		- Rapport de la première soutenance
|		- Rapport de la deuxième soutenance
|		- Rapport de la dernière soutenance
|
|	Dossier Site Web :
|		- Contient l'intégralité du site internet
|
|	Dossier Projet Complet :
|		- Contient les parties fonctionnelles de notre projet
|
|________________________________________________________________________________________________________________________________________
|
|	- Projet Complet :
|	|	- Interface utilisateur
|	|	- Raspberry
|	|	- Serveur :
|	|	|	- API
|	|	|	- Serveur
|
|	Le dossier Serveur et API doivent tous deux être installés dans le même dossier sur la machine d'hébergement du serveur.
|	
|	Le dossier Interface utilisateur doit être installé sur la machine de l'utilisateur connectée au même réseau internet que le serveur.
|
|	Le dossier Raspberry doit être installé sur le RaspberryPi relié à la cafetière et connecté au même réseau internet que le serveur.
|
|_________________________________________________________________________________________________________________________________________
|
|	Installation des bibliothèques à installer :
|		
|		Sur le serveur : 
|			- la bibliothèque jansson ( sur ubuntu : "sudo apt-get install -y libjansson-dev" )
|			- la bibliothèque Pthread ( sur ubuntu :"sudo apt-get install pthread" )
|
|		Sur la machine du client :
|			- la bibliothèque GTK ( sur ubuntu :"sudo apt-get install libgtk-3-dev" )
|		
|		Sur le RaspberryPi :
|			- la bibliothèque WiringPI ( sur raspbian "sudo apt-get install wiringpi" )
|
|
|_________________________________________________________________________________________________________________________________________
|
|	Utilisation des programmes : 
|
|		La première action à réaliser est de compiler la partie serveur grâce au Makefile fourni.
|		Vous pouvez désormais démarrer le serveur avec la commande "./serveur".
|		Une fois démarré, le serveur affiche "<Serveur started>" ainsi que son adresse IP dans l'invite de commande.
|
|		A ce moment là, la prochaine action est de compiler et de lancer la partie sur le RaspberryPi grâce au Makefile et la commande "./Rasp".
|		Il est alors demandé de renseigner une adresse IP, veuillez entrer l'IP renvoyé précédemment par le serveur.
|		Le RaspberryPi est maintenant connecté au serveur.
|
|		La dernière étape consiste à compiler et lancer l'interface utilisateur grâce au Makefile et la commande "./interface".
|		Il est alors demandé de renseigner une adresse IP, veuillez entrer l'IP renvoyé précédemment par le serveur.
|		L'interface utilisateur est maintenant connectée au serveur.
|
|		Afin de fermer le serveur il est nécessaire de valider deux fois l'interruption.
|__________________________________________________________________________________________________________________________________________