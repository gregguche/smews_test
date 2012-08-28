/*
* Copyright or © or Copr. 2011, Michael Hauspie
*
* Author e-mail: michael.hauspie@lifl.fr
*
* This software is a computer program whose purpose is to design an
* efficient Web server for very-constrained embedded system.
*
* This software is governed by the CeCILL license under French law and
* abiding by the rules of distribution of free software.  You can  use,
* modify and/ or redistribute the software under the terms of the CeCILL
* license as circulated by CEA, CNRS and INRIA at the following URL
* "http://www.cecill.info".
*
* As a counterpart to the access to the source code and  rights to copy,
* modify and redistribute granted by the license, users are provided only
* with a limited warranty  and the software's author,  the holder of the
* economic rights,  and the successive licensors  have only  limited
* liability.
*
* In this respect, the user's attention is drawn to the risks associated
* with loading,  using,  modifying and/or developing or reproducing the
* software by the user in light of its specific status of free software,
* that may mean  that it is complicated to manipulate,  and  that  also
* therefore means  that it is reserved for developers  and  experienced
* professionals having in-depth computer knowledge. Users are therefore
* encouraged to load and test the software's suitability as regards their
* requirements in conditions enabling the security of their systems and/or
* data to be ensured and,  more generally, to use and operate it in the
* same conditions as regards security.
*
* The fact that you are presently reading this means that you have had
* knowledge of the CeCILL license and that you accept its terms.
*/
/*
<generator>
        <handlers init="init_dynamic" doGet="get_dynamic"/>
	<properties persistence="volatile" />
	<args>
                <arg name="size" type="uint16" />
        </args>
</generator>
 */

#ifndef TEST_ARRAY_SIZE
  #ifdef DEV_MTU
    #define ARRAY_SIZE ((DEV_MTU-150) < 0 ? OUTPUT_BUFFER_SIZE : (DEV_MTU-150))
  #else
    #define ARRAY_SIZE OUTPUT_BUFFER_SIZE
  #endif
#else
  #define ARRAY_SIZE TEST_ARRAY_SIZE
#endif

static char array[ARRAY_SIZE];

static char init_dynamic(void)
{
    int i,j;
    for (i = 0,j=32 ; i < ARRAY_SIZE ; ++i,++j)
    {
		if (j == 126)
			j = 32;
		switch (i % 80)
		{
			case 0: array[i] = '\r'; --j; break;
			case 1: array[i] = '\n'; --j; break;
			default: array[i] = j;
		}
    }
    array[ARRAY_SIZE-1] = 0;
    return 1;
}

static char get_dynamic(struct args_t *args)
{
    uint32_t i = 0;
    uint16_t size = args->size;

    if (size == 0)
	out_c('0');
    while (i++ < size)
	out_str(array);
    return 1;
}
