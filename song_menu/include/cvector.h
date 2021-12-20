#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define DEFAULT_CAP 8
#define GROWTH_FACTOR 2
#define PADDING (sizeof(size_t) * 2)

#define cvector(type) type *	

#define size(vec) 			((size_t*)(vec))[-1]
#define capacity(vec) 		((size_t*)(vec))[-2]
#define set_size(vec, sz)	((size_t*)(vec))[-1] = (sz)
#define set_cap(vec, cap) 	((size_t*)(vec))[-2] = (cap)
#define empty(vec) 			(size((vec)) == 0)

static void* cvector_init(size_t type_sz)
{
	const size_t cvec_sz = PADDING + DEFAULT_CAP * type_sz;

	size_t *cvec_mem = malloc(cvec_sz);
	assert(cvec_mem);
	cvec_mem[0] = DEFAULT_CAP;
	cvec_mem[1] = 0;
	void *ret = (void*)(&cvec_mem[2]);

	return ret;
}

#define vec_expand(vec, cap)												\
	do {																	\
		const size_t new_sz = PADDING + (cap) * sizeof(*(vec));				\
		size_t *off_set = &((size_t*)(vec))[-2];							\
		size_t *new_vec = realloc(off_set, new_sz);							\
		assert(new_vec);													\
		(vec) = (void*)(&new_vec[2]);										\
	} while (0)

#define reserve(vec, cap)													\
	do {																	\
		if ((cap) > size((vec))) {											\
			vec_expand((vec), (cap));										\
			set_cap((vec), (cap));											\
		}																	\
	} while (0)

#define push_back(vec, elem)												\
	do {																	\
		if (size((vec)) >= capacity((vec))) {								\
			capacity((vec)) *= GROWTH_FACTOR;								\
			vec_expand((vec), capacity((vec)));								\
		}																	\
		vec[size((vec))] = elem;											\
		size((vec))++;														\
	} while (0)																\

#define pop_back(vec)														\
	do {																	\
		set_size((vec), size((vec)) - 1);									\
	} while (0)		

#define erase(vec, i)														\
	do {																	\
		if (i < size((vec))) {												\
			set_size((vec), size((vec)) - 1);								\
			for (size_t j = i; j < size((vec)); ++j) 						\
				(vec)[j] = (vec)[j + 1];									\
		}																	\
	} while (0)

#define back(vec) &((vec)[size((vec)) - 1])

#define begin(vec) (vec)

#define end(vec) &((vec)[size((vec))])

#define swap(vec, i, j) 													\
	do {																	\
		void *tmp = malloc(sizeof(*vec));									\
		memcpy(tmp, vec + i, sizeof(*vec));									\
		memcpy(vec + i, vec + j, sizeof(*vec));								\
		memcpy(vec + j, tmp, sizeof(*vec));									\
		free(tmp);															\
	} while (0)

#define cvector_free_destructor(vec, destructor)							\
	do {																	\
		for (size_t i = 0; i < size((vec)); ++i) {							\
			(destructor)(&(vec)[i]);										\
		}																	\
		size_t *tmp = &((size_t*)(vec))[-2];								\
		free(tmp);															\
	} while (0)		

#define cvector_free(vec)													\
	do {																	\
		size_t *tmp = &((size_t*)(vec))[-2];								\
		free(tmp);															\
	} while (0)		

#endif