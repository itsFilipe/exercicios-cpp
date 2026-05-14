i'm learning stl , the library that has functions, data structure, algorithims, iterators, the teacher is saying it's super powerfull, cause once you understand how it works, its the same pattern for all containers, it does not matter if its a vector or a list or a map, there are some points that needs to pay attention of course, i'm learning it, the main one the teacher keeps talking about is that it works nice with primitve data, but with objects that the user has created it can be tricky, because the stl will call the operators if needed, and the class needs to overload them, a example is calling the eqaulity operator '==', the stl will call it for the class, and it has to be overloaded!

exercicios:

Dado um vector de inteiros:
  → ordene e remova duplicatas          (sort + unique + erase)
  → encontre a mediana                  (sort + acesso por índice)
  → conte quantos são primos            (count_if + lambda)
  → some apenas os negativos            (accumulate + lambda)
  → separe positivos de negativos       (partition)

Dado um vector de strings:
  → coloque tudo em maiúsculo           (transform + toupper)
  → encontre a mais longa               (max_element com comparador)
  → remova as que têm menos de 3 chars  (remove_if + erase)
