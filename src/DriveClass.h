/**********************************************************************************
 * MIT License
 * 
 * Copyright (c) 2018 Antoine Beauchamp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *********************************************************************************/

#ifndef SA_DRIVETYPES_H
#define SA_DRIVETYPES_H

#include <string>

namespace shellanything
{

  enum DRIVE_CLASS
  {
    DRIVE_CLASS_UNKNOWN,
    DRIVE_CLASS_REMOVABLE,
    DRIVE_CLASS_FIXED,
    DRIVE_CLASS_NETWORK,
    DRIVE_CLASS_OPTICAL,
    DRIVE_CLASS_RAMDISK
  };

  /// <summary>
  /// Define if the given path is a network path.
  /// The given path do not need to exist to be identified as a network path.
  /// </summary>
  /// <param name="path">The path to a valid file or directory.</param>
  /// <returns>Returns true when the given path is a network path. Returns false otherwise.</returns>
  bool IsNetworkPath(const std::string & path);

  /// <summary>
  /// Returns the drive class based on the given path.
  /// </summary>
  /// <param name="path">The path to a valid file or directory.</param>
  /// <returns>Returns the drive class based on the given path. Returns DRIVE_CLASS_UNKNOWN if drive class cannot be found.</returns>
  DRIVE_CLASS GetDriveClassFromPath(const std::string & path);

  /// <summary>
  /// Returns the drive class based on the given string.
  /// The given string value must match one of the values returned by the ToString() function.
  /// </summary>
  /// <param name="value">The string representation of a DRIVE_CLASS.</param>
  /// <returns>Returns the given drive type based on the given string. Returns DRIVE_CLASS_UNKNOWN if the string value is unknown.</returns>
  DRIVE_CLASS GetDriveClassFromString(const std::string & value);
    
  /// <summary>
  /// Convert a DRIVE_CLASS value to a string representation.
  /// </summary>
  /// <param name="class_">The drive class value to convert. Must be a valid enumeration of DRIVE_CLASS.</param>
  /// <returns>Returns the string representation of the given DRIVE_CLASS enumeration value. Returns "drive:unknown" if 'class_' is not a valid value of DRIVE_CLASS.</returns>
  const char * ToString(DRIVE_CLASS & value);

} //namespace shellanything

#endif //SA_DRIVETYPES_H
