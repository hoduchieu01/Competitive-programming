Unit Meter;
Interface
  Function Size:Integer;
  Function Span(x,y:Integer):Integer;
  Procedure Answer(i:Integer; x:Integer);

Implementation
Const
  MaxN=10000;
  Init:Boolean=True;
  Test:Boolean=False;
  Pr=999999001;
Type
  Map=Array[1..MaxN] Of Integer;
Var
  N:Integer;
  P,
  CP,
  Acc:Map;
  MetinF,
  OutF:Text;
  MaxA:Integer;
  Sign:Longint;

Procedure Abort(M:String);
Begin
  WriteLn(OutF,M);
  Close(OutF);
  Halt;
End;

Procedure T1( P:Map; Var Q:Map);
  Var x,xx,y:Integer;
    L:Integer;
  Begin
    L:=P[1]+1; If L>N Then L:=N;
    For x:=1 To N Do Begin
      xx:=P[x];
      If (xx Mod L=0) Then
        y:=xx-L+1
      Else If xx<N Then
        y:=xx+1
      Else
        y:=(xx div L)*L+1;
      Q[y]:=x;
    End;
  End;

Procedure Initialise;
Var
  x,y:Longint;
  Sign0:Longint;
  Q:Map;
Begin
  Assign(OutF, 'chain.out');
  Rewrite(OutF);
  Assign(MetInF, 'chain.in');
  {$I-}
    Reset(MetInF);
  {$I+}
  If IOResult<>0 Then
    Abort('ERROR: Input file CHAIN.IN not found!');
  {$I-}
    ReadLn(MetInF,N);
  {$I+}
  If (IOResult<>0) Then  Begin
    Close(MetInF);
    Abort('ERROR: Non-number value in first line of CHAIN.IN');
  End;
  If (N<3) Or (N>MaxN) Then  Begin
    Close(MetInF);
    Abort('ERROR: Value out of range in first line of CHAIN.IN');
  End;

  For x:=1 To N Do Begin
    Q[x]:=-1;
    CP[x]:=0;
    ACC[x]:=0;
  End;
  For x:=1 To N Do Begin
    If SeekEoLn(MetInF) Then  Begin
      Close(MetInF);
      Abort('ERROR: Number of items in second line of file CHAIN.IN less then required');
    End;
    {$I-}
      Read(MetInF,y);
    {$I+}
    If (IOResult<>0) Then  Begin
      Close(MetInF);
      Abort('ERROR: Non-number value in second line of file CHAIN.IN');
    End;
    If (y<1) Or (y>N) Then  Begin
      Close(MetInF);
      Abort('ERROR: Value out of range in second line of file CHAIN.IN');
    End;
    If (Q[y]<>-1) Then  Begin
      Close(MetInF);
      Abort('ERROR: Duplicate values in second line of file CHAIN.IN');
    End;

    Q[y]:=x;
  End;

  ReadLn(MetInF);
  If EoF(MetInF) Then
    Sign0:=-1
  Else Begin
    {$I-}
      ReadLn(MetInF,Sign0);
    {$I+}
    If IOResult<>0 Then
      Sign0:=-1
  End;
  Close(MetInF);

  Test:=False;

  T1(Q,P);

  Sign:=0;
  For x:=1 To N Do Begin
    y:=P[x];
    Sign:=(Sign+(MaxN-x)*y) Mod Pr;
  End;

  If Sign<>Sign0 Then Begin
    P:=Q;
  End Else Begin
    Test:=True;
    For x:=1 To N Do
      Q[P[x]]:=x;
    P:=Q;
  End;

  MaxA:=0;
  Init:=False;
End{Initialise};

Function Size:Integer;
Begin
  If Init Then
    Initialise;
  Size:=N;
  WriteLn(OutF,'Size=',N:1);
  Flush(OutF);
End;

Procedure Answer(i:Integer;x:Integer);
Var
  Si,Sx:String;
  ii:Integer;
Begin
  If (i<1)Or(i>N)Or(x<1)Or(x>N) Then Begin
    Str(i,Si); Str(x,Sx);
    Abort('ERROR: in Answer('+Si+','+Sx+')');
  End;
  CP[i]:=x;
  If i=N Then Begin
    WriteLn(OutF,'Your Answer:');
    For ii:=1 To N-1 Do
      Write(OutF,CP[ii]:1,' ');
    WriteLn(OutF,CP[N]:1);
    WriteLn(OutF,'Access/Atom:');
    WriteLn(OutF,MaXA);
    If Test Then Begin
      WriteLn(OutF,'Signature:');
      WriteLn(OutF,Sign);
    End;
    Close(OutF);
    Halt;
  End;
End{Answer};

Function Span(x,y:Integer):Integer;
Var d:Integer;
Begin
  If Init Then
    Abort('ERROR: Illegal Dialogue! Size must be called first!');
  If (x<1) Or (x>N) Or (y<1) Or (y>N) Then Begin
    WriteLn(OutF,'Span(',x:1,',',y:1,')');
    Flush(OutF);
    Abort('ERROR: Parameter out of range in call Span!');
  End;
  If x=y Then
    Inc(Acc[x])
  Else Begin
    Inc(Acc[x]); Inc(Acc[y]);
  End;

  d:=Abs(P[x]-P[y]);
  WriteLn(OutF,'Span(',x:1,',',y:1,')=',d:1);
  Flush(OutF);
  If  (Acc[x]>MaxA) Then
    MaxA:=Acc[x];
  If  (Acc[y]>MaxA) Then
    MaxA:=Acc[y];

  If MaxA>4 Then Begin
    Assign(OutF, 'chain.out'); Rewrite(OutF);
    WriteLn(OutF,MaxA);
    WriteLn(OutF);

    Abort('ERROR: Illegal Dialogue! Atom accessed more than four times.');
  End;
  Span:=d;
End;

End.
