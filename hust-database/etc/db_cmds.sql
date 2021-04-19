
drop table fans_3, follow, thumb, mblog, my_users, sub, hot_posts, chan;
--- cleanup done

create table my_users(
    uid int not null unique primary key,
    name text,
    sex text,
    byear int,
    city text
);
------- 1
create table mblog(
    bid int not null unique primary key,
    title text,
    uid int references my_users,
    pyear int,
    pmonth int,
    pday int,
    cont text
);
create table thumb(
    uid int,
    bid int
);



---------- 2

insert into my_users values (101, 'recolic', 'M', 2016, 'WU HAN');
insert into mblog values (1, 'You mother sucks fuck you', 101, 1970, 1, 1, 'Hello world. This is testing content...');

delete from mblog where bid = 1;

update mblog set title = 'YOU ARE ATTACKED!!!' where bid = 1;

----------


---------- prepare 3
insert into my_users values (1, 'Trump', 'M', 2001, 'SAN FRANCISCO');
insert into my_users values (2, 'John', 'M', 1932, 'CITY OF INDUSTRY');
insert into my_users values (3, 'Jenny', 'F', 1932, 'SAN JOSE');
insert into my_users values (4, 'San Zhang', 'M', 1977, 'N CAROLINA');
create table follow (
    follower int references my_users(uid),
    following int references my_users(uid)
);
insert into follow values (1, 3); -- 3 follows 1
insert into follow values (2, 3); -- 3 follows 2
insert into follow values (3, 2); -- 2 follows 3
insert into follow values (4, 1); -- 4 follows 1
insert into follow values (4, 2); -- 4 follows 2
insert into follow values (4, 3); -- 4 follows 3
create table fans_3 (like my_users including all);
--------- 3
insert into fans_3 
    (uid, name, sex, byear, city)
    select uid, name, sex, byear, city
    from my_users
    where uid in (select follower from follow where following = 3);

------------------- 17 Questions

---------- Q1
select * from my_users
where uid in (
	select following from follow
	where follower=4
) order by byear desc, uid asc;

---------- Prepare Q2
insert into mblog values (1, 'You mother sucks fuck you', 101, 1970, 1, 1, 'Hello world. This is testing content...');
insert into mblog values (2, 'MOMMY MOMMY MOMMY MOMMY', 101, 1970, 1, 2, 'testing content 2');
insert into mblog values (3, '最多地铁站hello_华中科技大学', 101, 1970, 1, 3, 'testing blog 3');
insert into thumb values (3, 1);
---------- Q2
select mblog.bid,mblog.title,my_users.name from mblog,my_users
where mblog.bid not in (
	select bid from thumb
) and my_users.uid = mblog.uid
order by title asc;
---------- Prepare Q3
create table hot_posts(
    bid int references mblog primary key
);
insert into hot_posts values (3);
---------- Q3
select mblog.bid from my_users, hot_posts, mblog
where
	my_users.byear > 2000 and
	my_users.city = 'WU HAN' and 
	my_users.uid = mblog.uid and 
	mblog.bid = hot_posts.bid;
---------- Prepare Q4
create table sub(
    uid int primary key,
    chan text[]
);
create table chan(
    name text primary key
);
insert into chan values ('文学');insert into chan values ('艺术');insert into chan values ('哲学');insert into chan values ('音乐');
insert into sub values (101, '{"文学"}');insert into sub values (1, '{"文学","艺术","哲学","音乐"}');
---------- Q4
select uid from sub
where array_length(chan, 1) = (select count(*) from chan);
---------- Q5
select uid, byear, city from my_users
where byear not between 1970 and 2010;
---------- Q6
select city, count(uid) from my_users
group by city;
---------- Q7
select city,byear,count(uid) from my_users 
group by city,byear
order by city asc,count(uid) desc;
---------- Prepare Q8
insert into thumb values (101, 2);insert into thumb values (101, 2);insert into thumb values (101, 2);insert into thumb values (101, 2);insert into thumb values (101, 2);
insert into thumb values (101, 2);insert into thumb values (101, 2);insert into thumb values (101, 2);insert into thumb values (101, 2);insert into thumb values (101, 2);
insert into thumb values (101, 2);insert into thumb values (101, 2);
---------- Q8
select bid from thumb
group by bid having count(uid)>10;
---------- Q9
select bid from (
	select thumb.bid,thumb.uid from thumb,my_users
	where thumb.uid=my_users.uid and my_users.byear>2000
) as tmp
group by bid having count(tmp.bid)>10;
---------- Prepare Q10
insert into hot_posts values (2);
---------- Q10
select hot_posts.bid,count(hot_posts.bid) from hot_posts
where bid in(
	select bid from(
		select bid,my_users.uid from thumb,my_users
		where thumb.uid=my_users.uid and my_users.byear>2000
	) as tmp
	group by bid having count(tmp.uid)>10
) group by bid;
---------- Q11
select uid from sub where '{"文学","艺术","哲学","音乐"}' && chan;
---------- Q12
select * from mblog where title like '%最多地铁站%' and title like '%_华中科技大学%';
---------- Q13
select a.follower,a.following from follow a,follow b
where a.follower=b.following and b.follower=a.following;
---------- Q1
---------- Q1
---------- Q1

