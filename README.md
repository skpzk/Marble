# marble


Changements:
- suppression de la class AudioOutput car elle est redondante (l'interface commune est AudioObject)
- regroupement de toute la logique de synthèse dans un class SynthChannel qui existe dans la note (pas forcément nécessaire mais ça isole la logique de synthèse de celle de l'ordre des notes)
- plus de Vca mais une interface commune ModScalar pour toute valeur à moduler (pour l'instant amplitude et interpolation)
- ajout d'un Modulator dans chaque SynthChannel qui regroupe les objets de modulation (lfo, envelope) et les références à toutes les valeurs modulables. On fixe les valeurs de la matrice de modulation dans Voices::modulate qui prend deux valeurs modType et modValue