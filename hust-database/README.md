# HUST FUCKING DATABASE LAB

> live demo: https://hustdb.recolic.net/ (Webpage may be invalidated soon)

[![Go Report Card](https://goreportcard.com/badge/github.com/recolic/hust-database)](https://goreportcard.com/report/github.com/recolic/hust-database)
![Codebuild Status](https://codebuild.us-west-1.amazonaws.com/badges?uuid=eyJlbmNyeXB0ZWREYXRhIjoibVFyaTh1MWx0cFUxQ1dxZ2ZleS90OVJlZU9IOGtJUU5zd3lSd0VYSXNpN3I5am9sN25iN3RDQkMvY1Bpb2tVWldoaTBVaE9SQ0tGWU1DeUJwaFFhZUJJPSIsIml2UGFyYW1ldGVyU3BlYyI6IjZ5WktiVEV5Sk5mM3M4eU0iLCJtYXRlcmlhbFNldFNlcmlhbCI6MX0%3D&branch=master)

## 题目1：电信收费管理系统

采用B/S或C/S模式实现一个电信收费管理系统软件。实现电信套餐种类、用户信息、客服代表、收款员等信息的管理。

要求：
1. 实现不同权限的浏览和更新。
2. 实现用户扣、缴费情况及帐户余额的查询。
3. 实现欠款用户使用状态的自动改变。
4. 实现客服代表的业绩统计功能。
5. 提供至少两种风格的查询报表。

## Warning

This site has many XSS and CSRF vulnerabilities. 

## Usage

```
docker run -d --restart=always --name hustdb -p 8088:8088 -v /srv/hustdb:/var/lib/postgres/data recolic/hustdb
```

## Screenshots

![](https://recolic.net/res/snap-0528-003628.png)

![](https://recolic.net/res/snap-0528-003914.png)

![](https://recolic.net/res/snap-0528-003927.png)

![](https://recolic.net/res/snap-0528-003935.png)

![](https://recolic.net/res/snap-0528-004050.png)

![](https://recolic.net/res/snap-0528-004111.png)

![](https://recolic.net/res/snap-0528-004126.png)
