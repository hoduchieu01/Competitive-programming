int pw(int x,int mul){
	if(mul == 1) return x;
	int ret = pw(x,mul/2);
	ret = (ret * ret) % mod;
	if(mul & 1) ret = (ret * x) % mod;
	return ret;
}