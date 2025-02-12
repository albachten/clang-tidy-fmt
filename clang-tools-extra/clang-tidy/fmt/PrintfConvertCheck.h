//===--- PrintfConvertCheck.h - clang-tidy-----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_FMT_PRINTFCONVERTCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_FMT_PRINTFCONVERTCHECK_H

#include "../ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace fmt {
/// Documentation goes here.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/fmt-printf-convert.html
class PrintfConvertCheck : public ClangTidyCheck {
public:
  PrintfConvertCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  bool isLanguageVersionSupported(const LangOptions &LangOpts) const override {
    return LangOpts.CPlusPlus;
  }
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace fmt
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_FMT_PRINTFCONVERTCHECK_H
