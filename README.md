# marble

Yo ! Je ne sais pas si tu as déjà compilé avec Qt, donc j'ai ajouté un dossier avec un hello world en qt et la configuration cmake correspondante, qu'il faudra éventuellement adapter à ton installation.

... et un autre dans le même esprit avec un test de Qwt et un example de classe utilisant Qt.

J'ai aussi ajouté une nouvelle classe AudioObject qui simplifie un peu la création de nouveaux objets audio et beaucoup le code d'AudioOutput.  
Tous les nouveaux objets devraient hériter d'AudioObject.  
Il n'y a plus besoin de toucher à AudioOutput à chaque création.  
Chaque nouvel objet doit réécrire une fonction output.  
Voilà, dis-moi ce que tu en penses !