#ITR TD4

Le TD suivant à pour but de proceder à une encapsulation des taches posix pour securiser leurs utilisation. On utilise donc une architecture de classe permettant d'automatiser au maximum leurs fonctionnement et de mettre à profit les constructeurs/destructeurs pour automatiser les creation/destructions de mutex. 


##Classe Thread

On programme une classe Thread. On utilise le constructeur pour mettre en place la politique d'ordonnancement Posix:

````C++
Thread::Thread(int schedPolicy) : m_schedPolicy(schedPolicy)
{
	pthread_t m_tid;
	pthread_attr_t m_attr;
	pthread_attr_init(&m_attr);
	pthread_attr_setschedpolicy(&m_attr, schedPolicy);
	pthread_attr_setinheritsched(&m_attr, PTHREAD_EXPLICIT_SCHED);
}
 
````

Cette classe met en place une methode virtuelle pure ``run()`` qui va etre overridé par les sous-classes de threads spécifiques.

Complétez la classe Thread avec les éléments indiqués sur la figure 1b ; référez-vous à la documentation Posix pour le paramétrage de la taille de la pile (stackSize) ; pour la méthode join() avec timeout, vous devrez utiliser la fonction Linux pthread_timedjoin_np()qui n’appartient pas au standard Posix ; en ce qui concerne la méthode statique sleep(), il s’agit juste d’une fonction permettant d’endormir le thread appelant durant le temps spécifié en millisecondes. Testez la classe ainsi complétée.




##Classes Mutex et Lock

Programmez les classes Mutex et Lock en reprenant les spécifications de la figure 2 et les explications du cours. Prévoyez dans le constructeur de Mutex la possibilité d’une protection contre l’inversion de priorité par héritage de priorité. Comme type de mutex Posix, choisissez le type récursif. 
Testez vos classes en ‎protégeant l’accès au compteur de la question précédente par un mutex.‎‎



Figure 2 : Spécification des classes Mutex et Lock.
##Classe Condition

Programmez la classe Condition en la faisant dériver de la classe Mutex et en reprenant l’interface ‎proposée dans le cours et reprise sur la figure 3.



Figure 3 : Spécification de la classe Condition.
Complétez la classe Thread avec un champ booléen started représentant l’état actif de la tâche ; protégez ce champ des accès concurrents à l’aide d’une Condition associée ; modifiez la méthode start() de sorte qu’on ne puisse pas relancer une tâche tant que son exécution précédente n’est pas terminée ; ajoutez une valeur de retour à start() : true si la tâche est effectivement démarrée par l’appel de start(), false si elle était déjà démarrée au moment de l’appel.

##Classe Semaphore

Dans le contexte multitâches, un sémaphore est une « boite à jetons » à accès concurrent :

en appelant sa méthode give(), on lui rajoute un jeton ;
en appelant sa méthode take() on lui retire un jeton ;
si le compteur de jetons du sémaphore est à zéro, l’appel de take() est bloquant, avec ou sans timeout ;
à sa création, le sémaphore peut être vide ou contenir un nombre quelconque de jetons ;
on peut définir un nombre maximal de jetons au delà duquel le sémaphore « sature », c’est-à-dire que l’appel de give() ne modifie pas son compteur ;
la méthode flush() ne rajoute pas de jetons mais libère l’emsemble des tâches bloquées par un appel take() ;
un sémaphore est qualifié de « binaire » si sa valeur maximale est 1, c’est-à-dire qu’il ne peut avoir que 2 états : vide (0) ou plein (1).
Programmez la classe Semaphore en reprenant l’interface ‎proposée dans le cours et reprise sur la figure 4.



##Classe Fifo multitâches

La figure 5 spécifie l’interface d’une classe template Fifo. L’appel à pop() doit être bloquant si la fifo est vide ; l’appel bloquant doit comprendre une version ‎avec timeout.

Programmez la classe Fifo en utilisant le conteneur C++ std::queue et testez-la en y accédant de manière concurrente par de multiples tâches productrices et consommatrices. Pour cela, utilisez une fifo de nombres entiers, faites produire par chaque tâche productrice une série d’entiers de 0 à n et mettez un place un mécanisme pour vérifier que tous les entiers produits par les tâches productrices ont bien été reçus par les tâches consommatrices.


