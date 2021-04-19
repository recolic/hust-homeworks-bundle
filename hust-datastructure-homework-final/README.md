# HUST data-structure homework (AVL tree)

>[Check Doc](https://www.dropbox.com/s/57peeu4sbrp4cdb/2018%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E8%AF%BE%E7%A8%8B%E8%AE%BE%E8%AE%A1%E4%BB%BB%E5%8A%A1%20%E5%8F%91%E5%B8%83%E7%A8%BF%281%29.docx?dl=0)

Licensed under modified Mozilla Public License 2.0.

Warning: this is not the final version. To pleasure the fucking teacher, you must contact me to get an ugly(but the teacher thinks it smells good) shit.

[I know what you're here for](https://github.com/recolic/hust-ds-homework-final/blob/master/src/lib/set.hpp)!

### Build

```sh
git clone --recursive https://github.com/recolic/hust-ds-homework-final.git # Maybe you must wait for a long time...
make bin
make test # If you want...
bin/hust-ds
bin/hust-ds < test/hustds-test.rfakesh
```

### How do I make teacher happy

|**Doc Wants**|**I Provide**|
|:---:|:---:|
|UI|general_ui.hpp|
|AVL|`avl::tree<T> avl::tree<T,true>`|
|InitAVL|`avl::tree<T>::tree`|
|DestroyAVL|`avl::tree<T>::clear`|
|SearchAVL|`avl::tree<T>::find avl::tree<T>::exist avl::tree<T>::count`|
|InsertAVL|`avl::tree<T>::insert`|
|DeleteAVL|`avl::tree<T>::erase`|
|TraverseAVL|`std::for_each(avl::tree<T>::cbegin(),avl::tree<T>::cend(),operation);`|
|ADT|`r::set<T> r::multiset<T>`|
|set_init|`r::set<T>::set`|
|set_destroy|`avl::tree<T>::clear`|
|set_insert|`avl::tree<T>::insert`|
|set_remove|`avl::tree<T>::erase`|
|set_intersection|`r::set<T>::operator^ r::multiset<T>::operator^`|
|set_union|`r::set<T>::operator+ r::multiset<T>::operator+`|
|set_difference|`r::set<T>::operator- r::multiset<T>::operator-`|
|set_size|`avl::tree<T>::size`|
|set_member|`avl::tree<T>::exist`|
|set_subset|`r::set<T>::contain r::multiset<T>::contain`|
|set_equal|`r::set<T>::operator== r::multiset<T>::operator==`|
|ApplicationLevel|person.hpp reflected_impl.hpp|
|HardDisk DataFile|db.hpp|

### Testing

- How to launch test

```sh
test/testgen.py 1000000 > test/1mtest.rfakesh
time bin/hust-ds < test/1mtest.rfakesh > /dev/null
mv test/test.json test/1mtest.json
bin/hust-ds
rfaketerm 0.3.1 ~ load test/1mtest.json
rfaketerm 0.3.1 ~ help 
```

- Performance (Application)

|Person Set Size|Total Operation|Time|
|:---:|:---:|:---:|
|1K|25K|0.05s|
|10k|250K|0.53s|
|100K|2.5M|5.62s|
|1M|25M|61.65s|

- Performance (AVL)

|Insertion(Worst case)|Deletion|Time|
|:---:|:---:|:---:|
|10M|-|3497ms|
|-|10M|2462ms|

- Functional

- [x] AVL
- [x] set
- [x] second degree friend
- [x] common friend
- [x] common following

- Large Data Set

- [x] AVL
- [x] set
- [x] second degree friend
- [x] common friend
- [x] common following

### Make Teacher happy

The teacher wants an standalone avl/set operating ui, so just decompress ./hust-ds-homework-avl.tar.xz, ln `hust-ds-homework-avl/src/lib/...` to `hust-ds-homework-final/src/lib/...`, then everything is ok!
