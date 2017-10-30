Unit Query;
Interface
  Function Size:Integer;
  Function Member(i,j:Integer):Integer;
  Procedure Answer(i:Integer);
Implementation
Const
  MaxN=30000;
  MaxL=16;
  Init:Boolean=True;
  B:Array[Boolean] of 0..1=(0,1);
Var
  N,
  M,
  Half,
  FullS,
  NQ:Integer;       {# queries}
  T:Array[0..MaxN] of Integer;
  D:Array[0..MaxN] of Integer;
  OutF:Text;
  Bit:Set of 0..15 Absolute M;

 Procedure EndQuery;
 Begin
   Assign(OutF, 'select.out'); Rewrite(OutF);
   Writeln(OutF, '0 Point'); Flush(OutF);
   Close(OutF);
   Halt;
  End{EndQuery};

  Procedure Start;
  Var i:Integer;
    InFile:Text;
  Begin
    Assign(OutF, 'select.out'); Rewrite(OutF);
    Assign(InFile, 'select.in'); Reset(InFile);
    ReadLn(InFile, N);
    Close(InFile);

    For i:=1 To N Do Begin
      T[i]:=-1;
      D[i]:=0;
    End;
    T[0]:=0; D[0]:=0;
    If Odd(N) Then M:=N Else M:=N-1;
    Half:=M div 2 +1;

    Init:=False;
    NQ:=0;
    FullS:=0;
    For i:=0 To MaxL-1 Do
      If i In Bit Then Inc(FullS);
  End{Start};

  Function Find(x:Integer):Integer;
  Var Nx,xx:Integer;
  Begin
    Nx:=x;
    While T[Nx]>0 Do Nx:=T[Nx];
    While x<>Nx Do Begin{path compression}
      xx:=T[x]; T[x]:=Nx;
      x:=xx;
    End;
    Find:=Nx;
  End{Find};

  Procedure Union(Var Nx:Integer; Ny:Integer);
  Var X:Integer;
  Begin
    If Nx=0 Then
      Nx:=Ny
    Else If Ny<>0 Then Begin
      If T[Nx]>T[Ny] Then Begin
        X:=Nx; Nx:=Ny; Ny:=X;
      End;
      T[Nx]:=T[Nx]+T[Ny];
      T[Ny]:=Nx;
    End;
  End{Union};

  Function Size:Integer;
  Begin
    If Init Then Start;
    WriteLn(OutF, 'Size= ',N); Flush(OutF);
    Size:=N;
  End{Size};

Function Member(i,j:Integer):Integer;
Var Ri,Rj,Di,Dj,Si,Sj:Integer;
  Ui,Vi,Uj,Vj:Integer;
  SDi,SDj:Integer;
  X:Word;
  SX:Set of 0..15 Absolute X;
  Ans:Boolean;
Begin
  If Init Then Begin
    Writeln(OutF, 'ERROR: Illegal dialog. Size must be called first!');
    EndQuery;
  End;
  write(OutF, i:1,' ',j,' ');
  If (i<1)Or(i>N)Or (j<1)Or(j>N) Then Begin
    writeln(OutF, i:1,' ',j:1);
    writeln(OutF, 'ERROR: Value out of range'); Flush(OutF);
    EndQuery;
  End;

  Inc(NQ);
  Ans:=False;
  Ri:=Find(i);
  Rj:=Find(j);
  Di:=D[Ri]; Dj:=D[Rj];
  If Ri=Rj Then Begin
    writeln(OutF, 1);Flush(OutF);
    Member:=1;
    Exit;
  End;
  If (Ri=Dj)Or(Rj=Di) Then Begin
    writeln(OutF, 0);Flush(OutF);
    Member:=0;
    Exit;
  End;
  Si:=Abs(T[Ri]); Sj:=Abs(T[Rj]);
  SDi:=Abs(T[Di]); SDj:=Abs(T[Dj]);
  If Si>=SDi Then Begin
    Ui:=Ri; Vi:=Di;
  End Else Begin
    Ui:=Di; Vi:=Ri;
    X:=Si; Si:=SDi; SDi:=X
  End;
  If Sj>=SDj Then Begin
    Uj:=Rj; Vj:=Dj;
  End Else Begin
    Uj:=Dj; Vj:=Rj;
    X:=Sj; Sj:=SDj; SDj:=X
  End;
  If Si+Sj>=Half Then Begin
    Union(Ui, Vj);
    Union(Vi, Uj);
    D[Ui]:=Vi; If Vi<>0 Then D[Vi]:=Ui;
    Ans:=(Find(i)=Find(j));
  End Else Begin
    If Si+Sj<=SDi+SDj+2 Then Begin
      Union(Ui, Uj);
      Union(Vi, Vj);
      D[Ui]:=Vi; If Vi<>0 Then D[Vi]:=Ui;
      Ans:=(Find(i)=Find(j));
    End Else Begin
      If Si+SDj=Sj+SDi Then Begin
        X:=Si+SDj+Sj+SDi;
        If SX * Bit=SX Then begin
          Union(Ui, Vj);
          Union(Vi, Uj);
          D[Ui]:=Vi; If Vi<>0 Then D[Vi]:=Ui;
          Bit:=Bit-SX;
          Dec(Half, Si+SDj);
	  Ans:=(Find(i)=Find(j));
        End Else Begin
          Union(Ui, Uj);
          Union(Vi, Vj);
          D[Ui]:=Vi; If Vi<>0 Then D[Vi]:=Ui;
	  Ans:=(Find(i)=Find(j));
        End;
      End Else begin{Si+SDj<>Sj+SDi}
        Union(Ui, Vj);
        Union(Vi, Uj);
        D[Ui]:=Vi; If Vi<>0 Then D[Vi]:=Ui;
	 Ans:=(Find(i)=Find(j));
      End;
    End;
  End;

  Member:=B[Ans];
  writeln(OutF,B[Ans]);  Flush(OutF);
End{Member};

Procedure Answer(i:Integer);
Var Ri, Di,x,y,Nx:Integer;
  Sum:Integer;
  OK:Boolean;
  G:Array[0..MaxN] Of Boolean;
  a,b:Integer;
Begin
  If Init Then Begin
    Writeln(OutF, 'ERROR: Illegal dialog. Size must be called first!');
    EndQuery;
  End;
  If (i<1)Or(i>N) Then Begin
    writeln(OutF, 'Your Answer: ',i);
    writeln(OutF, 'ERROR: Value out of range');
    EndQuery;
  End;

  Ri:=Find(i);
  Di:=D[Ri];
  Sum:=0;

  For x:=1 To N Do Begin
    Nx:=Find(x);
    G[x]:= (Nx<>Ri)And(
           (T[Nx]<T[D[Nx]])Or
           (T[Nx]=T[D[Nx]]) And (Nx<D[Nx])Or
           (Nx=Di)
                      );
  End;
  For x:=1 To N Do
    If (T[x]<0)And(x<>Di)And(x<>Ri) Then Begin
      y:=D[x];
      If T[x]<T[y] Then
        Sum:=Sum+Abs(T[x])
      Else
        Sum:=Sum+Abs(T[y]);
      T[x]:=0; T[y]:=0;
    End;
  {for x=1..N};
  Sum:=Sum+Abs(T[Di]);
  OK:=Sum<N Div 2+1;

  If OK Then
    WriteLn(OutF, 'Your Answer: ',i, ', Correct')
  Else
    WriteLn(OutF, 'Your Answer: ',i, ', Not Correct');

  If OK Then
    WriteLn(OutF, 'Majority Group:')
  Else
    WriteLn(OutF, 'Non-Majority Group:');
  a:=0; b:=0; G[0]:=True; G[N+1]:=True;
  For x:=1 To N+1 Do Begin
    If Not G[x] Then Begin
      If Not G[x-1] Then
        b:=x
      Else Begin
        a:=x; b:=a;
      End;
    End Else Begin
      If a+1<b Then
        Write(OutF, a:1,'..',b:1,' ')
      Else If a<b Then
        Write(OutF, a:1,' ',b:1,' ')
      Else If (b=a)And(a<>0) Then
        Write(OutF, a:1,' ');
      b:=0;
    End;
  End; WriteLn(OutF);
  If OK Then
    WriteLn(OutF,'Non-Majority Group:')
  Else
    WriteLn(OutF,'Majority Group:');
  a:=0; b:=0; G[0]:=False; G[N+1]:=False;
  For x:=1 To N+1 Do Begin
    If G[x] Then Begin
      If G[x-1] Then
        b:=x
      Else Begin
        a:=x; b:=a;
      End;
    End Else Begin
      If a+1<b Then
        Write(OutF, a:1,'..',b:1,' ')
      Else If a<b Then
        Write(OutF, a:1,' ',b:1,' ')
      Else If (b=a)And(a<>0) Then
        Write(OutF, a:1,' ');
      b:=0;
    End;
  End; WriteLn(OutF);

  WriteLn(OutF, 'Number of Queries: ',NQ:1,' ');

  If OK Then Begin
    Sum:=N-NQ; If Sum<0 Then Sum:=0;
    WriteLn(OutF,'Full Possible Score: ', FullS);
    WriteLn(OutF,'Your Score: ',Sum:1);
  End Else Begin
    WriteLn(OutF,'Full Possible Score: ', FullS);
    WriteLn(OutF,'Your Score: ',0:1);
  End;
 Close(OutF);
End{Answer};

End.
