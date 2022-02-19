//===--- TraceConverterCheck.cpp -clang-tidy---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UnnecessaryCStrCheck.h"
#include "FormatStringConverter.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/FormatString.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace fmt {

void UnnecessaryCStrCheck::registerMatchers(MatchFinder *Finder) {

 using namespace clang::ast_matchers;

 // const auto StringClassExpr =
 //      expr(hasType(cxxRecordDecl(hasName("::std::basic_string"))));
 // const auto WStringClassExpr =
 //      expr(hasType(cxxRecordDecl(hasName("::std::wstring"))));

 auto StringType = hasUnqualifiedDesugaredType(recordType(hasDeclaration(cxxRecordDecl(hasName("::std::basic_string")))));
// auto PrintCall = hasUnqualifiedDesugaredType(functionType(hasDeclaration(functionDecl(hasName("::fmt::print")))));
 auto PrintCall = hasName("::fmt::print");
  StatementMatcher CStrMatcher = traverse(
      TK_AsIs, callExpr(callee(functionDecl(PrintCall)),
                        hasAnyArgument(cxxMemberCallExpr(
                                            callee(cxxMethodDecl(hasName("c_str"))),
                                            on(hasType(StringType)))))
      .bind("c_str"));

  Finder->addMatcher(CStrMatcher, this);
  llvm::outs() << "Registering matchers\n";
}

void UnnecessaryCStrCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Call = Result.Nodes.getNodeAs<CXXMemberCallExpr>("c_str");
  llvm::outs() << "Found c_str\n";


}

} // namespace fmt
} // namespace tidy
} // namespace clang
