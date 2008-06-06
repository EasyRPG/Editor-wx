TODO: main
main: SDK/CRpgLmt.o SDK/CRpgIOBase.o SDK/CBerStream.o SDK/CRpgArray.o SDK/CRpgUtil.o \
      SDK/sueLib/CBasicStream.o SDK/CBer.o
SDK/CRpgLmt.o: SDK/CRpgIOBase.o 
SDK/CRpgIOBase.o: SDK/CBerStream.o SDK/CRpgArray.o SDK/CRpgUtil.o
SDK/CBerStream.o: SDK/sueLib/CBasicStream.o 
SDK/sueLib/CBasicStream.o:

SDK/CRpgArray.o: SDK/sueLib/CMapTable.o
SDK/sueLib/CMapTable.o:
SDK/CRpgUtil.o: SDK/CBer.o SDK/CRpgArray.o
SDK/CBer.o: 

clean:
	rm SDK/sueLib/*.o SDK/*.o main
