// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

template <typename Type>
struct PROJECT_HIVE_API TPriorityQueueNode
{
	Type Element;
	float Priority;

	TPriorityQueueNode() = default;

	TPriorityQueueNode(Type InElement, float InPriority)
	{
		Element = InElement;
		Priority = InPriority;
	}

	// Lower number means higher priority
	bool operator<(const TPriorityQueueNode<Type>& Other) const
	{
		return Priority < Other.Priority;
	}
};

template <typename Type>
class PROJECT_HIVE_API TPriorityQueue
{
public:
	TPriorityQueue()
	{
		Array.Heapify();
	}

	~TPriorityQueue() = default;

	// Always check if IsEmpty() before Pop-ing!
	Type Pop()
	{
		TPriorityQueueNode<Type> Node;
		Array.HeapPop(Node);
		return Node.Element;
	}

	TPriorityQueueNode<Type> PopNode()
	{
		TPriorityQueueNode<Type> Node;
		Array.HeapPop(Node);
		return Node;
	}

	void Push(Type Element, float Priority)
	{
		Array.HeapPush(TPriorityQueueNode<Type>(Element, Priority));
	}

	bool IsEmpty() const
	{
		return Array.IsEmpty();
	}

private:
	TArray<TPriorityQueueNode<Type>> Array;
};
