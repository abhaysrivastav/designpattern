int main()
{
  VisualComponent* textView = new TextView(); 
  VisualComponent* scrollTextView = new ScrollDecorator(textView);
  VisualComponent* borderScrollTextView = new BorderDecorator(scrollTextView);

  delete textView;
  delete scrollableTextView;
  delete borderedScrollableTextView;

  return 0;
}
