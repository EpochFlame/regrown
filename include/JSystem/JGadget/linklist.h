#ifndef LINKLIST_H
#define LINKLIST_H

#include "types.h"
#include "algorithm"
#include "iterator"

namespace JGadget {
struct TLinkListNode {
	TLinkListNode()
	{
		mNext = nullptr;
		mPrev = nullptr;
	}

	TLinkListNode* mNext;
	TLinkListNode* mPrev;
};

struct TNodeLinkList {
	struct iterator : public std::iterator<std::input_iterator_tag, TLinkListNode> {
		iterator(TLinkListNode* pNode) { mNode = pNode; }
		iterator(const iterator& iter) { *this = iter; }

		TLinkListNode* mNode;
	};

	struct TPRIsEqual_pointer_ {
		/** @fabricated */
		bool operator()(TLinkListNode* other) { return other == mNode; }

		TLinkListNode* mNode;
	};

	TNodeLinkList()
	    : mLinkListNode()
	{
		Initialize_();
	}
	void Initialize_()
	{
		mCount              = 0;
		mLinkListNode.mNext = &mLinkListNode;
		mLinkListNode.mPrev = &mLinkListNode;
	}

	/** @fabricated */
	iterator start() { return iterator(&mLinkListNode); }

	iterator end()
	{
		iterator iter(mLinkListNode.mNext);
		return iter;
	}

	~TNodeLinkList();
	void Insert(TNodeLinkList::iterator, TLinkListNode*);
	void Erase(TLinkListNode*);
	void Remove(TLinkListNode*);
	void remove_if(TPRIsEqual_pointer_);

	// unused/inlined:
	void erase(iterator);
	void erase(iterator, iterator);
	void clear();
	void splice(iterator, TNodeLinkList&);
	void splice(iterator, TNodeLinkList&, iterator);
	void splice(iterator, TNodeLinkList&, iterator, iterator);
	void swap(TNodeLinkList&);
	void reverse();
	TLinkListNode* Find(const TLinkListNode*);

	int mCount;                  // _00
	TLinkListNode mLinkListNode; // _04
};

template <typename T, int I>
struct TLinkList : public TNodeLinkList {
	TLinkList()
	    : TNodeLinkList()
	{
	}

	struct iterator : TNodeLinkList::iterator {
		typedef const T& reference;
		iterator(TNodeLinkList::iterator iter)
		    : TNodeLinkList::iterator(iter)
		{
		}

		/** @fabricated */
		bool operator==(const iterator& other) const { return (&other == this); }
		/** @fabricated */
		bool operator!=(const iterator& other) const { return (&other != this); }
		/** @fabricated */
		iterator& operator++()
		{
			++mNode;
			return *this;
		}
		/** @fabricated */
		reference operator*() const { return *(const T*)(((u8*)&mNode) + I); }
	};

	TLinkListNode* Element_toNode(T* element) const { return reinterpret_cast<TLinkListNode*>(reinterpret_cast<u8*>(element) + I); }

	void Insert(TLinkList::iterator iter, T* element)
	{
		TLinkListNode* node = Element_toNode(element);
		TNodeLinkList::Insert(iter, node);
	}

	iterator Erase(T* element)
	{
		TLinkListNode* node = Element_toNode(element);
		return ((TNodeLinkList*)this)->Erase(node);
	}

	/** @fabricated */
	TLinkList::iterator start()
	{
		TNodeLinkList::iterator node_iter = TNodeLinkList::start();
		TLinkList::iterator iter(node_iter);
		return iter;
	}

	TLinkList::iterator end()
	{
		TNodeLinkList::iterator node_iter = TNodeLinkList::end();
		TLinkList::iterator iter(node_iter);
		return iter;
	}

	void Push_back(T* element)
	{
		TLinkList::iterator iter(TLinkList::end());
		this->Insert(iter, element);
	}

	// _00-_08	= TNodeLinkList
};

template <typename T, int Offset>
struct TLinkList_factory : public TLinkList<T, Offset> {
	virtual ~TLinkList_factory() = 0; // _08
	virtual T* Do_create()       = 0; // _0C
	virtual void Do_destroy(T*)  = 0; // _10

	// _00-_08	= TNodeLinkList
	// _0C		= VTABLE
};
}; // namespace JGadget

#endif
