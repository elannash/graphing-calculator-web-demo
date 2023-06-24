#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>

#include "../../includes/system/system.h"
#include "../../includes/sidebar/sidebar.h"
#include "../../includes/constants/constants.h"
#include "../../includes/tokenizer/tokenizer.h"

using namespace std;

bool float_equal(const float lhs, const float rhs) //for float comparison in translator test
{
  float epsilon = 0.001;
  if (abs(lhs - rhs) < epsilon)
  {
    return true;
  }
  return false;
}

bool test_tokenizer(bool debug = false)
{
  string test_string = "X^2-SIN(X*MAX(2,X))";

  Queue<Token *> expected;
  expected.push(new Variable("X"));
  expected.push(new Operator("^"));
  expected.push(new Number(2));
  expected.push(new Operator("-"));
  expected.push(new Function("SIN"));
  expected.push(new LeftParen);
  expected.push(new Variable("X"));
  expected.push(new Operator("*"));
  expected.push(new SpecialFunction("MAX"));
  expected.push(new LeftParen);
  expected.push(new Number(2));
  expected.push(new Variable("X"));
  expected.push(new RightParen);
  expected.push(new RightParen);

  Tokenizer tkzr(test_string);
  Queue<Token *> tkzr_result = tkzr();

  cout << tkzr.get_pre_tokenized_str() << endl;

  Queue<Token *>::Iterator it(tkzr_result.begin());

  for (Queue<Token *>::Iterator it2(expected.begin()); it2 != expected.end() || it != tkzr_result.end(); it2++, it++)
  {
    if ((*it)->get_string() != (*it2)->get_string())
    {
      cout << "TOKENIZER FAILED TO PRODUCE EXPECTED RESULT. expected: " << endl
           << expected << endl
           << "result: " << endl
           << tkzr_result << endl
           << "FAILED ON EXPECTED CHAR: " << (*it)->get_string() << " INSTEAD FOUND: " << (*it2)->get_string() << endl;
      return false;
    }
  }
  cout << "TOKENIZER SUCCESSFULLY TOKENIZED STRING." << endl;

  return true;
}

bool test_translator(bool debug = false)
{
  Graph_Info *g_info = new Graph_Info;
  g_info->_domain = (sf::Vector2f(-6, 6));
  g_info->_equation = "x^2";
  g_info->_origin = (sf::Vector2f(WORK_PANEL / 2, WORK_PANEL / 2));
  g_info->_points = 10;
  g_info->_range = (sf::Vector2f(-6, 6));

  //this uses constants
  translate translator(g_info);

  vector<sf::Vector2f> expected;
  expected.push_back(sf::Vector2f(WORK_PANEL / 2, WORK_PANEL / 2));
  expected.push_back(sf::Vector2f(0, WORK_PANEL / 2));
  expected.push_back(sf::Vector2f(WORK_PANEL / 2, 0));
  expected.push_back(sf::Vector2f(WORK_PANEL, WORK_PANEL / 2));
  expected.push_back(sf::Vector2f(WORK_PANEL / 2, WORK_PANEL));

  expected.push_back(sf::Vector2f(0, 0));
  expected.push_back(sf::Vector2f(WORK_PANEL, WORK_PANEL));
  expected.push_back(sf::Vector2f(WORK_PANEL, 0));
  expected.push_back(sf::Vector2f(0, WORK_PANEL));

  vector<sf::Vector2f> result;
  result.push_back(translator(sf::Vector2f(0, 0)));
  result.push_back(translator(sf::Vector2f(-6, 0)));
  result.push_back(translator(sf::Vector2f(0, 6)));
  result.push_back(translator(sf::Vector2f(6, 0)));
  result.push_back(translator(sf::Vector2f(0, -6)));

  result.push_back(translator(sf::Vector2f(-6, 6)));
  result.push_back(translator(sf::Vector2f(6, -6)));
  result.push_back(translator(sf::Vector2f(6, 6)));
  result.push_back(translator(sf::Vector2f(-6, -6)));

  vector<sf::Vector2f>::iterator it2 = result.begin();

  for (vector<sf::Vector2f>::iterator it = expected.begin(); it != expected.end(); it++, it2++)
  {
    if (!(float_equal(it->x, it2->x) && float_equal(it->y, it2->y)))
    {
      cout << "TRANSLATED POINT IS NOT THE SAME AS EXPECTED POINT: " << endl
           << "EXPECTED: (" << it->x << " " << it->y << ")" << endl
           << "TRANSLATED: (" << it2->x << " " << it2->y << ")" << endl
           << endl;
      return false;
    }
  }
  cout << "TRANSLATOR SUCCESSFULLY TRANSLATED POINTS." << endl;

  return true;
}

bool test_plotter(bool debug = false)
{
  //no tests here because plotter just brings together all the classes and doesn't really add any new code
  //and manually pushing a bunch of expected points into a vector isn't fun
  return true;
}

bool test_shunting_yard(bool debug = false)
{
  Queue<Token *> infix;
  Queue<Token *> expected;

  //3/(5-(6+7)/(2+8*4))*9
  //3567+284*+/-/9*

  expected.push(new Number(3));
  expected.push(new Number(5));
  expected.push(new Number(6));
  expected.push(new Number(7));
  expected.push(new Operator("+"));
  expected.push(new Number(2));
  expected.push(new Number(8));
  expected.push(new Number(4));
  expected.push(new Operator("*"));
  expected.push(new Operator("+"));
  expected.push(new Operator("/"));
  expected.push(new Operator("-"));
  expected.push(new Operator("/"));
  expected.push(new Number(9));
  expected.push(new Operator("*"));

  infix.push(new Number(3));
  infix.push(new Operator("/"));
  infix.push(new LeftParen());
  infix.push(new Number(5));
  infix.push(new Operator("-"));
  infix.push(new LeftParen());
  infix.push(new Number(6));
  infix.push(new Operator("+"));
  infix.push(new Number(7));
  infix.push(new RightParen);
  infix.push(new Operator("/"));
  infix.push(new LeftParen);
  infix.push(new Number(2));
  infix.push(new Operator("+"));
  infix.push(new Number(8));
  infix.push(new Operator("*"));
  infix.push(new Number(4));
  infix.push(new RightParen);
  infix.push(new RightParen);
  infix.push(new Operator("*"));
  infix.push(new Number(9));

  ShuntingYard sy(infix);
  Queue<Token *> postfix = sy.postfix();

  Queue<Token *>::Iterator it = expected.begin();
  Queue<Token *>::Iterator it2 = postfix.begin();

  for (; it != expected.end(); it++, it2++)
  {
    if ((*it)->get_string() != (*it2)->get_string())
    {
      return false;
    }
  }
  cout << "SHUNTING YARD SUCCESSFULLY TRANSLATED TO POSTFIX." << endl;

  return true;
}

bool test_rpn(bool debug = false)
{
  string test_string = "X^2+24-5*X";
  Tokenizer tkzr(test_string);
  RPN rpn;
  ShuntingYard sy;
  sy.infix(tkzr());
  rpn.set_input(sy.postfix());

  if (rpn(0) != 24)
  {
    cout << "EXPECTED 24, FOUND: " << rpn(0) << endl;
    return false;
  }
  if (rpn(1) != 20)
  {
    cout << "EXPECTED 20, FOUND: " << rpn(1) << endl;
    return false;
  }
  if (rpn(2) != 18)
  {
    cout << "EXPECTED 18, FOUND: " << rpn(2) << endl;
    return false;
  }
  if (rpn(5) != 24)
  {
    cout << "EXPECTED 24, FOUND: " << rpn(5) << endl;
    return false;
  }

  test_string = "MAX(X, SIN(X))";
  tkzr.set_pre_tokenized_str(test_string);
  sy.infix(tkzr());
  rpn.set_input(sy.postfix());

  if (rpn(0) != 0)
  {
    cout << "EXPECTED 0, FOUND: " << rpn(0) << endl;
    return false;
  }
  if (rpn(1) != 1)
  {
    cout << "EXPECTED 1, FOUND: " << rpn(1) << endl;
    return false;
  }

  test_string = "MIN(X, SIN(X))";
  tkzr.set_pre_tokenized_str(test_string);
  sy.infix(tkzr());
  rpn.set_input(sy.postfix());

  if (!float_equal(rpn(3.14159), 0))
  {
    cout << "EXPECTED 0, FOUND: " << rpn(3.14159) << endl;
    return false;
  }

  test_string = "X2SIN";
  tkzr.set_pre_tokenized_str(test_string);
  sy.infix(tkzr());
  rpn.set_input(sy.postfix());
  rpn();

  if (!rpn.fail())
  {
    cout << "RPN SHOULD BE IN FAIL STATE, BUT WASN'T" << endl;
    return false;
  }
  cout << "RPN SUCCESSFULLY EVALUATED INPUTS." << endl;

  return true;
}

TEST(TEST_RPN, TestRpn)
{
  EXPECT_EQ(1, test_rpn(false));
}

TEST(TEST_SHUNTING_YARD, TestShuntingYard)
{
  EXPECT_EQ(1, test_shunting_yard(false));
}

TEST(TEST_TOKENIZER, TestTokenizer)
{
  EXPECT_EQ(1, test_tokenizer(false));
}

TEST(TEST_TRANSLATOR, TestTranslator)
{
  EXPECT_EQ(1, test_translator(false));
}

TEST(TEST_PLOTTER, TestPlotter)
{
  EXPECT_EQ(1, test_plotter(false));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running testB.cpp---------\n\n"
            << std::endl;
  return RUN_ALL_TESTS();
}
