# marble

Yo ! J'ai ajouté une fonction que j'utilise souvent pour le debug, qui affiche le fichier, la fonction et la ligne qui sont en train d'écrire quelque chose dans le terminal.

usage :
```
#include "Utils/DebugUtils.h"

std::cout << dline() << "message" << std::endl;
// ou bien
printf("%s message", dline());

```
