
/**
Student(S#,Sname,Sage,Ssex) ѧ���� 
Course(C#,Cname,T#) �γ̱� 
SC(S#,C#,score) �ɼ��� 
Teacher(T#,Tname) ��ʦ�� 
**/

select * from Student
select * from Course
select * from SC
select * from Teacher

--1����ѯ��001���γ̱ȡ�002���γ̳ɼ��ߵ�����ѧ����ѧ�ţ� 
select a.S#, c.Sname from 
(select S#,score from SC where C#=001) a, 
(select S#,score from SC where C#=002) b, 
Student c 
where a.score > b.score and a.S#=b.S# and c.S#=a.S#

--2����ѯƽ���ɼ�����60�ֵ�ͬѧ��ѧ�ź�ƽ���ɼ��� 
select S#,avg(score) from SC group by S# having avg(score) > 60
select a.Sname, b.S#, b.avgs from Student a, (select S#,avg(score) as avgs from SC group by S# having avg(score) > 80) b where a.S#=b.S#

--3����ѯ����ͬѧ��ѧ�š�������ѡ�������ܳɼ��� 
select a.S#, a.Sname, b.CourseCount, b.SumScore, b.AvgScore from Student a, 
(select S#, count(C#) as CourseCount, sum(score) as SumScore, avg(score) as AvgScore from SC group by S#) b
where a.S#=b.S#

--4����ѯ�ա������ʦ�ĸ�����
select count(T#) from Teacher where Tname like 'Li %'

--5����ѯûѧ����Ҷƽ����ʦ�ε�ͬѧ��ѧ�š�����

--XXX!!!Wrong
select x.S#,x.Sname from Student x,
( select distinct(S#),C# from SC where C# not in (select distinct(a.C#) from SC a, Course b, Teacher c where a.C#=b.C# and b.T#=c.T# and c.Tname='Yang HL') ) y
where x.S#=y.S#

--right
   select Student.S#,Student.Sname 
    from Student  
    where S# not in (select distinct( SC.S#) from SC,Course,Teacher where  SC.C#=Course.C# and Teacher.T#=Course.T# and Teacher.Tname='Yang HL')

