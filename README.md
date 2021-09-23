# otus-filter-ip

* Актуальный исходный код в ветке main
* Настроен CI в github
* Подключен googte test (через submodules) для юнит тестирования + написан тривиальный тест

```
mkdir build
cd build
cmake .. -DPATCH_VERSION=1
cmake --build .
cmake --build . --target test
cmake --build . --target package
cat ../ip_filter.tsv | ./ipfilter | md5sum
```