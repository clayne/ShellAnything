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

#ifndef SA_ACTION_MESSAGE_H
#define SA_ACTION_MESSAGE_H

#include "shellanything/Action.h"

namespace shellanything
{

  /// <summary>
  /// Action class that prompts the user for a value.
  /// </summary>
  class ActionMessage : public Action
  {
  public:
    ActionMessage();
    virtual ~ActionMessage();

    /// <summary>
    /// Prompts the user for a value.
    /// </summary>
    /// <param name="iContext">The current context of execution.</param>
    /// <returns>Returns true if the execution is successful. Returns false otherwise.</returns>
    virtual bool Execute(const Context & iContext) const;

    /// <summary>
    /// Getter for the 'title' parameter.
    /// </summary>
    const std::string & GetTitle() const;

    /// <summary>
    /// Setter for the 'title' parameter.
    /// </summary>
    void SetTitle(const std::string & iTitle);

    /// <summary>
    /// Getter for the 'caption' parameter.
    /// </summary>
    const std::string & GetCaption() const;

    /// <summary>
    /// Setter for the 'caption' parameter.
    /// </summary>
    void SetCaption(const std::string & iCaption);

    /// <summary>
    /// Getter for the 'icon' parameter.
    /// </summary>
    const std::string & GetIcon() const;

    /// <summary>
    /// Setter for the 'icon' parameter.
    /// </summary>
    void SetIcon(const std::string & iIcon);

  private:
    std::string mTitle;
    std::string mCaption;
    std::string mIcon;
  };

} //namespace shellanything

#endif //SA_ACTION_MESSAGE_H
