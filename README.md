# binomial_heap
Тут реализация очень плохая: слишком часто происходит вызов деструктора у Node<T>, и, таким образом у нас на каждом шаге происходит n проходок по logn и сложность вырастает до n^2 logn(если не больше, например log^2 n). Это происходит из - за того, что вершины хранятся в массиве, а не в двусвязном списке. Если использовать двусвязный список, то сразу становится доступно множество оптимизация, например, теперь добавляя новый элемент мы сразу его пакуем в Node<T> и смотрим, какой ранг у первого элемента в двусвязном списке, если не 0 -> халявное добавление, если 0 -> добавляем до первого неравенства.


Причем!!! Не использовать новые конструкторы, чтобы избежать бесконечных вызовов деструкторов.

В итоге, должно получиться in_place Insert()

что насчет merge_Trees()? Ну, правую отрезаем, меняем указатели и все.
-> можно сделать inline ибо слишком частые вызовы, по сути через 1.

!!ExtractMin дико-жестко плодит утечку памяти, если у меня в куче было 8 элементов и я достал минимум, то стало в куче 7 элементов и еще где-то не удаленных 10 висит


Короче, все это жестко фиксить надо.
