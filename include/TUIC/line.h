/*
	Copyright (c) 2021 Daniel Valcour

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/*! \file line.h
 */
#ifndef TUIC_LINE_H //header guard
#define TUIC_LINE_H
#ifdef __cplusplus //extern C guard
extern "C" {
#endif
#include <TUIC/types.h>
#include <TUIC/grid_shape_types.h>
#include <TUIC/boolean.h>


/*! @name Line Functions
 *
 * Functions for manipulating @ref TuiLine.
 *  @{ */
/*!
* @brief Create a @ref TuiLine.
*
* @param start_x The x position of the start point.
* @param start_y The y position of the start point.
* @param end_x The x position of the end point.
* @param end_y The y position of the end point.
*
* @returns The created @ref TuiLine.
*
* @errors This function can have no errors.
*
* @requirements This function can be called freely, even if TUIC is not currently initialized.
*
* @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
*/
TuiLine tuiLine(const int start_x, const int start_y, const int end_x, const int end_y);
/*!
* @brief Get the starting point of a @ref TuiLine.
*
* @param line THe @ref TuiLine.
*
* @returns The starting @ref TuiPoint2.
*
* @errors This function can have no errors.
*
* @requirements This function can be called freely, even if TUIC is not currently initialized.
*
* @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
*/
TuiPoint2 tuiLineGetStartPoint2(const TuiLine line);
/*!
* @brief Get the ending point of a @ref TuiLine.
*
* @param line THe @ref TuiLine.
*
* @returns The ending @ref TuiPoint2.
*
* @errors This function can have no errors.
*
* @requirements This function can be called freely, even if TUIC is not currently initialized.
*
* @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
*/
TuiPoint2 tuiLineGetEndPoint2(const TuiLine line);
/*!
 * @brief Get the length of a @ref TuiLine.
 *
 * @param line The @ref TuiLine.
 *
 * @returns The length of the line.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
float tuiLineGetLength(const TuiLine line);
/*!
 * @brief Get the diagonal length of a @ref TuiLine.
 *
 * @param line The @ref TuiLine.
 *
 * @returns The diagonal length length of the line.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
int tuiLineGetDiagonalLength(const TuiLine line);
/*!
 * @brief Get the cross product of two @ref TuiLine.
 *
 * @param line_1 The first @ref TuiLine.
 * @param line_2 The second @ref TuiLine.
 *
 * @returns The cross product.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
int tuiLinesGetCrossProduct(const TuiLine line_1, const TuiLine line_2);
/*!
 * @brief Get the dot product of two @ref TuiLine.
 *
 * @param line_1 The first @ref TuiLine.
 * @param line_2 The second @ref TuiLine.
 *
 * @returns The dot product.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
float tuiLinesGetDotProduct(const TuiLine line_1, const TuiLine line_2);
/*!
 * @brief Get if two @ref TuiLine are parallel.
 *
 * @param line_1 The first @ref TuiLine.
 * @param line_2 The second @ref TuiLine.
 *
 * @returns The @ref TuiBoolean result. If the lines are parallel, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiLinesParallel(const TuiLine line_1, const TuiLine line_2);
/*!
 * @brief Get if two @ref TuiLine are collinear.
 *
 * @param line_1 The first @ref TuiLine.
 * @param line_2 The second @ref TuiLine.
 *
 * @returns The @ref TuiBoolean result. If the lines are collinear, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiLinesCollinear(const TuiLine line_1, const TuiLine line_2);
/*!
 * @brief Get if two @ref TuiLine are perpendicular.
 *
 * @param line_1 The first @ref TuiLine.
 * @param line_2 The second @ref TuiLine.
 *
 * @returns The @ref TuiBoolean result. If the lines are perpendicular, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiLinesPerpendicular(const TuiLine line_1, const TuiLine line_2);
/*!
 * @brief Get if two @ref TuiLine contains a @ref TuiPoint2.
 *
 * @param line The @ref TuiLine.
 * @param point2 The @ref TuiPoint2.
 *
 * @returns The @ref TuiBoolean result. If the line contains the point, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiLineContainsPoint2(const TuiLine line, const TuiPoint2 point2);
/*!
 * @brief Get if a @ref TuiLine contains a different @ref TuiLine.
 *
 * @param line_1 The @ref TuiLine.
 * @param line_2 The @ref TuiLine to check for.
 *
 * @returns The @ref TuiBoolean result. If the line contains the line, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiLineContainsLine(const TuiLine line_1, const TuiLine line_2);
/*!
 * @brief Get if two @ref TuiLine intersect each other.
 *
 * @param line_1 The first @ref TuiLine.
 * @param line_2 The second @ref TuiLine.
 *
 * @returns The @ref TuiBoolean result. If the lines intersect, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiLineIntersectsLine(const TuiLine line_1, const TuiLine line_2);
/*!
 * @brief Get if a @ref TuiLine intersects a @ref TuiRect.
 *
 * @param line The @ref TuiLine.
 * @param rect The @ref TuiRect.
 *
 * @returns The @ref TuiBoolean result. If line and rect intersect, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiLineIntersectsRect(const TuiLine line, const TuiRect rect);
/*! @} */


#ifdef __cplusplus //extern C guard
}
#endif
#endif //header guard