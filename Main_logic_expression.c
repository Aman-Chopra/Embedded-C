
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void push(float symbol);
float pop();
void infix_to_postfix();
void infix_to_newinfix();
int priority(char symbol);
int isEmpty();
int white_space(char);
float eval_post();
char infix[100], postfix[100];
float stack[100];
char answer[100];
float key[100];
char infix_new[100];
int top;

int main()
{
    top=-1;
    int i = 0;
    scanf("%[^\n]s",infix);
    infix_to_newinfix();
    printf("%s\n",infix_new);
    infix_to_postfix();
    printf("%s\n",postfix);
    float ans = eval_post();
    printf("%s\n",answer);//Final char Array for lcd puts
    return 1;
}

void infix_to_newinfix()//Method to convert expression entered by user into a new_infix made by encoding multiple digits into a single digit
//using hashing technique i.e., using key value pairs.
{
    int count = 1;
    int i = 0;
    int val = 0;
    int j = 0;
    int k = 0;
    int co = 0;
    int reverse=0;
    int flag = 0;
    for(i=0;i<=strlen(infix);i++)
    {
        if(infix[i]>=48 && infix[i]<=57)
        {
            int tempVal = infix[i]-'0';
            if(tempVal==0)
            {
                val = val*count;
                flag = 1;
            }
            else
                val += tempVal * count;
                count = count*10;
        }
        else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^' || infix[i] == 'r' || infix[i] == '\0')
        {
            count = 1;
            if(infix[i-1] != ')')
            {
                if(flag!=1)
                {
                        while (val != 0)
                        {
                            reverse = reverse * 10;
                            reverse = reverse + val%10;
                            val = val/10;
                        }
                        key[j] = reverse;
                        infix_new[k++] = j+'0';
                        infix_new[k++] = infix[i];
                }
                else
                {
                        key[j] = val;
                        infix_new[k++] = j+'0';
                        infix_new[k++] = infix[i];
                }
                j++;
                val = 0;
                reverse = 0;
                flag = 0;
            }
            else
            {
                infix_new[k++] = infix[i];
                j++;
                val = 0;
                reverse = 0;
                flag = 0;
            }
        }
        else if(infix[i]=='(')
        {
            infix_new[k++] = infix[i];
        }
        else if(infix[i] == ')')
        {
            key[j] = val;
            infix_new[k++] = j+'0';
            infix_new[k++] = infix[i];
            j++;
            val = 0;
            reverse = 0;
            flag = 0;
        }
        else
        {

        	infix_new[k++] = infix[i];
        	i++;
        	count=1;
        	while(infix[i]>=48 && infix[i]<=57)
        	{
        		int tempVal = infix[i]-'0';
        		if(tempVal==0)
                {
                    val = val*count;
                    flag = 1;
                }
                else
                    val += tempVal * count;
        		count = count*10;
        		i++;
        	}
        	if(flag!=1)
            {
                while(val != 0)
                {
                    reverse = reverse * 10;
                    reverse = reverse + val%10;
                    val = val/10;
                }
                key[j] = reverse;
                infix_new[k++] = j+'0';
                infix_new[k++] = infix[i];
            }
            else
            {
                key[j] = val;
                infix_new[k++] = j+'0';
                infix_new[k++] = infix[i];
            }
        	j++;
        	reverse = 0;
        	val = 0;
        	flag = 0;
        }
    }
}

void infix_to_postfix()//Method to convert the new_infix to postfix for postfix evaluation
{
    int i,p=0;
    char next;
    char symbol;
    for(i=0; i<strlen(infix_new); i++)
    {
        symbol=infix_new[i];
            switch(symbol)
            {
            case '(':
                push(symbol);
                break;
            case ')':
                while((next=pop())!='(')
                    postfix[p++] = next;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case 'r':
            case 's':
            case 'c':
            case 't':
            case 'l':
                while( !isEmpty( ) &&  priority(stack[top])>= priority(symbol) )
                    postfix[p++]=pop();
                push(symbol);
                break;
            default: /*if an operand comes*/
                postfix[p++]=symbol;
            }
    }
    while(!isEmpty( )){
        postfix[p++]=pop();
    }

    postfix[p]='\0'; /*End postfix with'\0' to make it a string*/
}

/*This function returns the priority of the operator*/
int priority(char symbol)
{
    switch(symbol)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
    case 'r':
        return 3;
    case 'l':
    case 's':
    case 'c':
    case 't':
        return 4;
    default :
        return 0;
    }
}

void push(float symbol)
{
    if(top>100)
    {
        exit(1);
    }
      stack[++top]=symbol;
}

float pop()
{
    if( isEmpty() )
    {
        exit(1);
    }
    return (stack[top--]);
}

int isEmpty()//checks the condition of stack underflow
{
    if(top==-1)
        return 1;
    else
        return 0;
}

int white_space(char symbol)
{
    if( symbol == ' ' || symbol == '\t' )
        return 1;
    else
        return 0;
}

float eval_post()//Method to evaluate the resultant postfix expression to get the resultant answer.
{
    float temp,result;
    float a,b;
    int i;
    for(i=0; i<strlen(postfix); i++)
    {

        if(postfix[i]<='9' && postfix[i]>='0'){
            float please = key[postfix[i]-'0'];//Taking the value of the char element and pushing it to float array
            push(please);
        }
        else
        {
            if(infix_new[0]=='l')
            {
                a=pop();
                infix_new[0]='a';
                temp = log2(a);
                push(temp);
            }
            else if(infix_new[0]=='s')
            {

                a=pop();
                infix_new[0]='a';
                temp = sin((a*3.141)/180);
                push(temp);
            }
            else if(infix_new[0]=='c')
            {
                a=pop();
                infix_new[0]='a';
                temp = cos((a*3.141)/180);
                push(temp);
            }
            else if(infix_new[0]=='t')
            {
                a=pop();
                infix_new[0]='a';
                temp = tan((a*3.141)/180);
                push(temp);
            }
            else
            {
                a=pop();
                b=pop();
                switch(postfix[i])
                {
                case '+':
                    temp=b+a;
                    push(temp);
                    break;
                case '-':
                    temp=b-a;
                    push(temp);
                    break;
                case '*':
                    temp=b*a;
                    push(temp);
                    break;
                case '/':
                    temp=b/a;
                    push(temp);
                    break;
                case '^':
                    temp=pow(b,a);
                    push(temp);
                    break;
                case 'r':
                    temp=pow(b,1/a);
                    push(temp);
                    break;
                case 'l':
                    temp = log2(a);
                    push(b);
                    push(temp);
                    break;
                case 's':
                    temp = sin((a*3.141)/180);
                    push(b);
                    push(temp);
                    break;
                case 'c':
                    temp = cos((a*3.141)/180);
                    push(b);
                    push(temp);
                    break;
                case 't':
                    temp = tan((a*3.141)/180);
                    push(b);
                    push(temp);
                    break;
                }
            }
        }
    }
    result=pop();
    char myCharPointer[100];
    sprintf(myCharPointer, "%f", result);//Converting final float answer to character array for lcd puts.
    int len = strlen(myCharPointer);
    len-=4;//Making the precision from 6 digit to 2 digits for cleaner answers.
    int y = 0;
    for(y=0;y<len;y++)
       answer[y] = myCharPointer[y];
    answer[y]='\0';
    return result;
}
