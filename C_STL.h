//
// C_STL.h
//
//      Copyright (c) CJL_sysu. All rights reserved.
//
// STL developed for C language
#pragma once
#include<stdio.h>
#include<malloc.h>
#include<memory.h>
#include<stdbool.h>
typedef int vtype;//You can change the type of vector here
typedef int ltype;//You can change the type of list here
//vector
struct vector
{
	vtype* vec;
	int capacity;
	int size;
};
void VMake(struct vector* v)
{
	v->capacity = 1;
	v->vec = (vtype*)malloc(v->capacity * sizeof(vtype));
	v->size = 0;
}
void VPush_back(struct vector* v, vtype val)
{
	if (v->size == v->capacity)
	{
		v->capacity = (int)(v->capacity * 1.5) > v->capacity ? (int)(v->capacity * 1.5) : v->capacity + 1;
		vtype* p = (vtype*)malloc(v->capacity * sizeof(vtype));
		memset(p, 0, sizeof(vtype) * (v->capacity));
		for (int i = 0; i < v->size; i++)
			p[i] = v->vec[i];
		vtype* rubbish = v->vec;
		v->vec = p;
		free(rubbish);
		rubbish = NULL;
	}
	v->vec[v->size++] = val;
}
void VPop_back(struct vector* v)
{
	v->vec[v->size - 1] = 0;
	v->size--;
}
int VSize(struct vector* v)
{
	return v->size;
}
int VCapacity(struct vector* v)
{
	return v->capacity;
}
vtype VAt(struct vector* v, int pos)
{
	if (pos >= 0 && pos < v->size)
	{
		return v->vec[pos];
	}
	else
	{
		printf("访问错误位置\n");
		return -1;
	}
}
void VResize(struct vector* v, int n)
{
	if (n > v->capacity)
	{
		v->capacity = n;
		vtype* p = (vtype*)malloc(sizeof(vtype) * v->capacity);
		memset(p, 0, sizeof(vtype) * (v->capacity));
		for (int i = 0; i < v->size; i++)
			p[i] = v->vec[i];
		v->size = n;
		vtype* rubbish = v->vec;
		v->vec = p;
		free(rubbish);
		rubbish = NULL;
	}
	else
	{
		v->size = n;
	}
}
void VInsert(struct vector* v, int pos, vtype val)
{
	if (pos<0 || pos>v->size)
	{
		printf("访问错误位置\n");
		return;
	}
	if (v->size == v->capacity)
	{
		v->capacity = (int)(v->capacity * 1.5) > v->capacity ? (int)(v->capacity * 1.5) : v->capacity + 1;
		vtype* p = (vtype*)malloc(v->capacity * sizeof(vtype));
		memset(p, 0, sizeof(vtype) * (v->capacity));
		for (int i = 0; i < v->size; i++)
			p[i] = v->vec[i];
		vtype* rubbish = v->vec;
		v->vec = p;
		free(rubbish);
		rubbish = NULL;
	}
	for (int i = v->size - 1; i >= pos; i--)
		v->vec[i + 1] = v->vec[i];
	v->vec[pos] = val;
}
void VChange(struct vector* v, int pos, vtype val)
{
	if (pos<0 || pos>=v->size)
	{
		printf("访问错误位置\n");
		return;
	}
	v->vec[pos] = val;
}
void VDelete(struct vector* v, int pos)
{
	if (pos < 0 || pos >= v->size)
	{
		printf("访问错误位置\n");
		return;
	}
	v->vec[pos] = 0;
	for (int i = pos; i < v->size - 1; i++)
		v->vec[i] = v->vec[i + 1];
	v->size--;
}
//list
struct lnode
{
	ltype data;
	struct lnode* next;
};
struct list
{
	struct lnode* start;
	struct lnode* end;
	int length;
};
void LMake(struct list* L)
{
	L->start = (struct list*)malloc(sizeof(struct list*));
	L->end = L->start;
	L->length = 0;
	L->start->next = NULL;
	L->start->data = 0;
}
bool LInsert_back(struct list* L,int pos,ltype data)
{
	if (pos < 0)
	{
		printf("错误位置\n");
		return false;
	}
	struct lnode* p = L->start;
	for (int it = 0; p != NULL && it < pos; it++)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		printf("数组越界\n");
		return false;
	}
	struct lnode* newnode = (struct lnode*)malloc(sizeof(struct lnode));
	if (newnode == NULL)
		return false;
	newnode->data = data;
	newnode->next = p->next;
	p->next = newnode;
	L->length++;
	if (newnode->next == NULL)
		L->end = newnode;
	return true;
}
bool LPush_back(struct list* L, ltype data)
{
	struct lnode* p = (struct lnode*)malloc(sizeof(struct lnode));
	p->data = data;
	p->next = NULL;
	L->end->next = p;
	L->end = p;
	L->length++;
	return true;
}
ltype LAt(struct list* L, int pos)
{
	if (pos < 0)
	{
		printf("错误位置\n");
		return -1;
	}
	struct lnode* p = L->start;
	for (int it = 0; p != NULL && it < pos; it++)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		printf("数组越界\n");
		return -1;
	}
	return p->data;
}
int LLength(struct list* L)
{
	return L->length;
}
bool LDelete(struct list* L, int pos)
{
	if (pos < 1)
	{
		printf("错误位置\n");
		return false;
	}
	struct lnode* p = L->start;
	for (int it = 0; p != NULL && it < pos-1; it++)
	{
		p = p->next;
	}
	struct lnode* tem = p;
	p = p->next;
	if (p == NULL)
	{
		printf("数组越界\n");
		return false;
	}
	tem->next = p->next;
	free(p);
	p = NULL;
	L->length--;
	return true;
}