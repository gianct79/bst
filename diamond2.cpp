/*
 * Copyleft 1979-2014 GTO Inc. All rights reversed.
 */

#include <iostream>
#include <stack>
#include <utility>

typedef std::pair<int, int> line;

void drawLine(line const &line)
{
  auto spaces = std::get<0>(line);
  auto stars = std::get<1>(line);

  for (; spaces > 0; spaces--)
    std::cout << ' ';
  for (; stars > 0; stars--)
    std::cout << '*';
  std::cout << '\n';
}

void drawShape(int &lines)
{
  if (lines < 1)
    return;

  auto spaces = lines - 1;
  auto stars = 1;

  std::stack<line> s;
  s.push(std::make_pair(spaces, stars));

  while (--lines)
  {
    drawLine(s.top());
    s.push(std::make_pair(--spaces, ++(++stars)));
  }

  while (!s.empty())
  {
    drawLine(s.top());
    s.pop();
  }
}

int main()
{
  int lines;
  while (std::cin >> lines)
    drawShape(lines);

  return 0;
}
