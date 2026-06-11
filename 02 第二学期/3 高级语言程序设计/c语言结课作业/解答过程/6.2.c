//链表实现选择排序
//其中p_0指向前边未排好序的节点，p0指向前一个
//p_1指向中间比较过的符合条件的节点，p1指向前一个节点
//p_2指向搜索的节点p2指向前一个节点
St *sort1(St *head)
{
    St *p0,*p_0,*p1,*p_1,*p2,*p_2;
    if(head==NULL) {puts("链表为空");return head;}
    p0=p_0=head;
    while(p_0->next!=NULL)
    {
        p1=p0;
		p_1=p2=p_0;
		p_2=p_0->next;
        while(p_2!=NULL)
        {
            if(p_1->sum < p_2->sum)
            {     
			    p1=p2;
				p_1=p_2;
			}
            p2=p_2;
			p_2=p_2->next ;   
        }
        if(p_0!=p_1)
        {
            p1->next=p_1->next;
            p_1->next=p_0;
            if(p_0==head) head=p_1;
            else p0->next =p_1;
            p0=p_1;
        }
        else 
		{
		    p0=p_0 ;
			p_0=p_0->next ;
		}
    }
    return head;
}
//链表实现气泡排序
//其中p p0 p1 分别指向相邻的三个节点，
//p_end指向最后一个未排好序的节点
struct STU* sort2(struct STU *head)
{
 struct STU *p,*p0,*p1,*p_end;
 int i;
 p_end=head;
 if(head==NULL)
 { puts("空链表！");return head;}
 while(p_end->next !=NULL)
  p_end=p_end->next ;
 while(head!=p_end)
 {
  i=0;
  p=p0=head,p1=p0->next ;
  while(p1!=p_end )
  {
   if(p0->sc >p1->sc)
   {
    p0->next =p1->next ;
    p1->next =p0;
    if(p0==head) head=p1;
    else  p->next =p1;
    p=p1,p1=p0->next ;
    i=1;
   }
   else { p=p0;p0=p1;p1=p1->next ;}       
  }
  if(p0->sc >p1->sc)
  {
   p0->next =p1->next ;
   p1->next =p0;
   if(p0==head) head=p1;
   else  p->next =p1;
   i=1;
  }
   else   p_end=p0 ;
   if(i==0)break;
 }
 return head;
}
