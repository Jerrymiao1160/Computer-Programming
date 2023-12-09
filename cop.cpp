//*** Don't submit the code segment below.
#include<iostream>
using namespace std;
int ccc =0;

class Matrix {
friend class Counter;
public:
	Matrix(int, int);
	~Matrix();
	void addAll(int);
	void assign(int, int, int);
	int getValue(int, int) const;
	void print(ostream&) const;
	int getHeight() const;
	int getWidth() const;
	Matrix *copy() const; // new member function!
private:
	int use; // new member variable!
	int h, w;
	int **matrix;
};


void Matrix::addAll(int v)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			matrix[i][j] += v;
		}
	}
}

void Matrix::assign(int r, int c, int s)
{
	matrix[r][c] = s;
}

int Matrix::getValue(int r, int c) const
{
	return matrix[r][c];
}

void Matrix::print(ostream& o) const
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			o << matrix[i][j];
			if (j == w - 1)
			{
				o << endl;
			}
			else
			{
				o << " ";
			}
		}
	}
}

int Matrix::getHeight() const
{
	return h;
}

int Matrix::getWidth() const
{
	return w;
}

Matrix *Matrix::copy() const
{	
	Matrix *ret = new Matrix(h, w);
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			ret->assign(i, j, matrix[i][j]);
		}
	}
	return ret;
}

class Counter {
public:
	Counter();
	Counter(int, int);
	~Counter();
	
	Counter& operator = (const Counter&);
	void addAll(int);
	void assign(int, int, int);
	int getValue(int, int) const;
	int getHeight() const;
	int getWidth() const;
	int getUse() const;
	friend ostream& operator<< (ostream&, const Counter&);
private:
	Matrix *p;
};

Counter::Counter() : p(nullptr) {}

Counter::Counter(int _h, int _w)
{
	p = new Matrix(_h, _w);
}

int Counter::getValue(int i, int j) const
{
	return p->getValue(i, j);
}

int Counter::getHeight() const
{
	return p->getHeight();
}

int Counter::getWidth() const
{
	return p->getWidth();
}

ostream& operator<< (ostream& o, const Counter& rhs)
{
	rhs.p->print(o);
	return o;
}

int Counter::getUse() const
{
	return p->use;
}

void printUse(Counter *mats, int numOfMat);

void printUse(Counter *mats, int numOfMat)
{
	for (int i = 0; i < numOfMat; ++i)
	{
		cout << "mats[" << i << "].getUse() = " << mats[i].getUse() << endl;
	}
	return;
}

//*** Don't submit the code segment above.


Matrix::Matrix(int _h, int _w) : use(1)
{
	cout<<"constuct new Matrix!"<<endl;
	ccc++;
    h=_h;
    w=_w;
    matrix= new int*[h];
    for(int i=0;i<h;i++) matrix[i]= new int[w];
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            matrix[i][j]=0;
        }
    }
}

Matrix::~Matrix()
{	
	cout<<"Hi Matrix destructor"<<endl;
	ccc--;
    for(int i=0;i<h;i++){
        delete []matrix[i];
    }
    delete []matrix;
}

Counter::~Counter()
{
	if(p==nullptr) delete p;
	if(p!=nullptr){
		if(p->use<=1){
			p->~Matrix();
			//cout<<"Hi Counter destructor(use<=1)"<<endl;
		}
		else{
			p->use--;
			//cout<<"Hi use--"<<endl;
		}
	}
}

Counter& Counter::operator = (const Counter& rhs)
{	
	if(this->p!=nullptr){
		this->p->use--;
		if(this->p->use==0) {
			cout<<"delete"<<endl;
			Matrix* temp=p;
			p=nullptr;
			temp->~Matrix();
			
		}
		rhs.p->use++;
	}
	else rhs.p->use++;
	this->p=rhs.p;
	
	return *this;
}

void Counter::addAll(int s)
{	
	if(this->p->use>1){
		this->p->use--;
		this->p=this->p->copy();
	}
	this->p->addAll(s);
}

void Counter::assign(int r, int c, int s)
{	
	if(this->p->use>1){
		this->p->use--;
		this->p=this->p->copy();
	}
	this->p->assign(r,c,s);
}



//*** Don't submit the code segment below.
int main()
{
	Counter mats[20];
	
	int numOfMat;
	cin >> numOfMat;
	
	for (int i = 0; i < numOfMat; ++i)
	{
		int h, w;
		cin >> h >> w;
		mats[i] = Counter(h, w);
	}
	
	int n;
	cin >> n;
	
	for (int i = 0; i < n; ++i)
	{
		int op;
		cin >> op;
		if (op == 0)
		{
			int idx1, idx2;
			cin >> idx1 >> idx2;
			mats[idx1] = mats[idx2];
		}
		else if (op == 1)
		{
			int idx1, s;
			cin >> idx1 >> s;
			mats[idx1].addAll(s);
		}
		else if (op == 2)
		{
			int idx1, r, c, s;
			cin >> idx1 >> r >> c >> s;
			mats[idx1].assign(r, c, s);
		}
		else if (op == 3)
		{
			int idx1;
			cin >> idx1;
			cout << mats[idx1];
		}
		
		printUse(mats, numOfMat);
		
	}
	cout<<"ccc= "<<ccc<<endl;
	return 0;
}
//*** Don't submit the code segment above.

