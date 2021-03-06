package com.example;

public class XLog {
	
	public static int LOG_MODE_SYNC = 0;
	public static int LOG_MODE_ASYNC = 1;
	
	private static String mLogPath;
	private static Level mLevel;
	private static boolean mSwitchStdOut = false;

	static
	{
		//���ؿ��ļ�
		System.loadLibrary("xlog");
	}
 
	public static void init(String path, int mode, Level level) {
		if (path != null && path.length() != 0) {
			mLogPath = path;
			nativeInitLog(path, mode, level.getValue());
		}
	}

    public static void close() {
    	nativeCloseLog();
    }
    
    public static void flush() {
    	nativeFlushLog();
    }
    
   
    public static void setSwitchStdOut(boolean switchStdOut) {
        mSwitchStdOut = switchStdOut;
        nativeSwitchStdOut(switchStdOut);
    }
        
   
    public synchronized static String getLogPath() {
        return mLogPath;
    }      

    
    public synchronized static Level getLevel() {
        return mLevel;
    }

    
    public static boolean isSwitchStdOut() {
        return mSwitchStdOut;
    } 
    
    public static void verbose(String tag, final String format, final Object... obj) {
        log(Level.VERBOSE, tag, format, obj);
    }

   
    public static void debug(String tag, final String format, final Object... obj) {
        log(Level.DEBUG, tag, format, obj);
    }

    
    public static void info(String tag, final String format, final Object... obj) {
        log(Level.INFO, tag, format, obj);
    }

   
    public static void warn(String tag, final String format, final Object... obj) {
        log(Level.WARN, tag, format, obj);
    }

   
    public static void error(String tag, final String format, final Object... obj) {
        log(Level.ERROR, tag, format, obj);
    }
    
    public static void fatal(String tag, final String format, final Object... obj) {
        log(Level.FATAL, tag, format, obj);
    }

    private static void log(Level level, String tag, final String format, final Object... obj) {
        String logInfo = obj == null ? format : String.format(format, obj);
        if (logInfo == null) {
            logInfo = "";
        }
    	String methodName = Thread.currentThread().getStackTrace()[4].getMethodName();
        String className = Thread.currentThread().getStackTrace()[4].getClassName();
        int line = Thread.currentThread().getStackTrace()[4].getLineNumber();  
        
        nativelog(level.getValue(), tag, "", className, methodName, line, logInfo);
    }
    
    private static void log(Level level, String tag, String logInfo) {
        String methodName = Thread.currentThread().getStackTrace()[4].getMethodName();
        String className = Thread.currentThread().getStackTrace()[4].getClassName();
        int line = Thread.currentThread().getStackTrace()[4].getLineNumber();  
        
        nativelog(level.getValue(), tag, "", className, methodName, line, logInfo);
    }

    private static native void nativeInitLog(String dir, int mode, int level);

    private static native void nativeCloseLog();

    private static native void nativelog(int level, String tag, String fileName, String className, String funName, int line, String msg);

    private static native void nativeFlushLog();
    
    private static native void nativeSwitchStdOut(boolean enable);
    
 
    private static int getLineNumber() {
        return Thread.currentThread().getStackTrace()[2].getLineNumber();
    }

    private static String getMethodName() {
        return Thread.currentThread().getStackTrace()[2].getMethodName();
    }

    private static String getFileName() {
        return Thread.currentThread().getStackTrace()[2].getFileName();
    }
}
