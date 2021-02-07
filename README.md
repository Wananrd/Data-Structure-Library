# Data-Structure-Library
数据结构的相关操作



	//此文档用来对写的这个数据结构库做注释

	//语言：C++，作者：WananRd

		//首先声明：程序中因为需要用到模板+类

		//模板的分文件编写会出现
			
			//问题：类模板中成员函数创建时机是在调用阶段，导致分文件编写时链接不到

			//解决方式1：直接包含.cpp源文件
			//解决方式2：将声明和实现写到同一个文件中，并更改后缀名为.hpp，.hpp是约定的名称，并不是强制



	//下面具体的内容做一个命名概述
		
		//1.Link_list	带头结点的单链表

			//LinkNode--结点
			//LinkList--链表

		//2.CircLink_list	带头结点的循环链表

			//CircLinkNode--结点
			//CircLinkList--链表

		//3.DoubleLink_list	带头结点的双向循环链表

			//DblNode--结点
			//DblList--链表

		//4.Link_Stack		链栈

			//LinkStack--链栈

		//5.Link_Queue		链队

			LinkQueue--链队

		//6.Astring			字符串

			Astring		字符串

		//7.BiTree			二叉树

			BiTreeNode--结点
			BinaryTree--二叉树

		//8.Hhffman_Tree	哈弗曼树（最优二叉树）

			HuffmanTree--结点
			HuffmanCode--编码

		//9.BiSort_Tree		二叉排序树

			BiSortTree--二叉排序树
			
