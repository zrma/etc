#pragma once

template<typename I, typename J>
auto Add(I i, J j) -> decltype(i + j)
{
	return i + j;
}

void DeclTypePractice();