# Тестирующая программа

## Запуск

Запуск тестирующей программы может производится, например, вот так:

```console
./bin/main >> data.csv
```
Прим.: перед этим программа должна быть скомпилирована (см. [CMakeLists.txt](CMakeLists.txt))

На выходе получем [файл](analyze/data.csv), содержащий следующие данные:

- `n`
- `merge_random`
- `merge_reversed`
- `merge_nearly`
- `merge_insert_5_random`
- `merge_insert_5_reversed`
- `merge_insert_5_nearly`
- `merge_insert_10_random`
- `merge_insert_10_reversed`
- `merge_insert_10_nearly`
- `merge_insert_20_random`
- `merge_insert_20_reversed`
- `merge_insert_20_nearly`
- `merge_insert_30_random`
- `merge_insert_30_reversed`
- `merge_insert_30_nearly`
- `merge_insert_50_random`
- `merge_insert_50_reversed`
- `merge_insert_50_nearly`
- `merge_insert_100_random`
- `merge_insert_100_reversed`
- `merge_insert_100_nearly`
- `merge_insert_200_random`
- `merge_insert_200_reversed`
- `merge_insert_200_nearly`
- `merge_insert_400_random`
- `merge_insert_400_reversed`
- `merge_insert_400_nearly`

То есть каждая строка содержит временные оценки для конкретного `n`
