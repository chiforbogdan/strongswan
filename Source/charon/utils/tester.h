/**
 * @file tester.h
 *
 * @brief Interface of tester_t.
 *
 */

/*
 * Copyright (C) 2005 Jan Hutter, Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef TESTER_H_
#define TESTER_H_

#include <stdio.h>

#include <types.h>


typedef struct test_t test_t;

typedef struct tester_t tester_t;

/**
 * @brief Representing a specified test.
 * 
 * @ingroup utils
 */
struct test_t {
	/**
	 * Testfunction called for this test.
	 * 
	 * @param tester		associated tester_t object
	 */
	void (*test_function) (tester_t * tester);
	/**
	 * Name of the test.
	 */
	char * test_name;
};

/**
 * A tester class to perform tests.
 * 
 * @ingroup utils
 */
struct tester_t {

	/**
	 * @brief Tests all testcases in array tests with specific tester_t object.
	 *
	 * @param tester 	tester_t object
 	 * @param tests		pointer	to an array of test_t-pointers.
 	 * 			      	The last item has to be NULL.
	 * @return			SUCCESS in any case
	 */
	status_t (*perform_tests) (tester_t *tester,test_t **tests);

	/**
	 * @brief Run a specific test case.
	 *
	 * @param this 		tester_t object
	 * @param test 		pointer to a test_t object which will be performed
	 * @return			SUCCESS in any case
	 */
 	status_t (*perform_test) (tester_t *tester, test_t *test);

	/**
	 * Is called in a testcase to check a specific situation for TRUE.
	 *
	 * Log-Values to the tester output are protected from multiple access.
	 *
	 * @warning This function should only be called in a test_function.
	 *
	 * @param this 			tester_t object
	 * @param to_be_true 	assert which has to be TRUE
	 * @param assert_name	name of the assertion
	 */
	void (*assert_true) (tester_t *tester, bool to_be_true, char *assert_name);

	/**
	 * Is called in a testcase to check a specific situation for FALSE.
	 *
	 * Log-Values to the tester output are protected from multiple access.
	 *
	 * @warning This function should only be called in a test_function.
	 *
	 * @param this 			tester_t object
	 * @param to_be_false 	assert which has to be FALSE
	 * @param assert_name	name of the assertion
	 */
	void (*assert_false) (tester_t *tester, bool to_be_false, char *assert_name);

	/**
	 * @brief Destroys a tester_t object
	 *
	 * @param tester 	tester_t object
	 * @return 			SUCCESS in any case
	 */
	status_t (*destroy) (tester_t *tester);
};

/**
 * @brief Creates a tester_t object used to perform tests with.
 *
 * @param output 					test output is written to this output.
 * @param display_succeeded_asserts has to be TRUE, if all asserts should be displayed,
 * 									FALSE otherwise
 *
 * @return							
 * 									- tester_t object
 * 									- NULL if out of ressources
 * 
 * @ingroup utils
 */
tester_t *tester_create(FILE *output, bool display_succeeded_asserts);

#endif /*TESTER_H_*/
