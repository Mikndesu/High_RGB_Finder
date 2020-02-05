#include <jni.h>

#include <iostream>
#include <cstdlib>
#include <string>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/log.h>


#define ATTR_POS 0


static const char* gsc_pszVShader = "attribute vec3 position;"
                                    "void main() {"
                                    "gl_Position = vec4(position, 1.0);"
                                    "}";

static const char* gsc_pszFShader_1 = "void main () {"
                                    "gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);"
                                    "}";

static const char* gsc_pszFShader_2 = "void main () {"
                                    "gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
                                    "}";



//----------------------------------------------------------------------------//
// シェーダプログラムコンパイル
// type GL_VERTEX_SHADER : 頂点シェーダ / GL_FRAGMENT_SHADER : フラグメントシェーダ
// pszProgram プログラム文字列
// return コンパイル結果生成されるシェーダオブジェクト / 失敗時は0を返却
//----------------------------------------------------------------------------//
GLuint CompileShaderProgram(GLenum type, const char *pszProgram)
{
    GLuint shaderId;
    GLint shaderCompiled;

    // シェーダオブジェクトの作成
    shaderId = glCreateShader(type);

    // ソースコードをシェーダオブジェクトに変換
    glShaderSource(shaderId, 1, (const char**)&pszProgram, NULL);

    // コンパイル
    glCompileShader(shaderId);

    // コンパイルエラーチェック
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompiled);
    if (!shaderCompiled)
    {
        __android_log_print(ANDROID_LOG_ERROR, "GLES2Sample1", "シェーダコンパイルに失敗");
        return 0;
    }

    return shaderId;
}

//----------------------------------------------------------------------------//
// シェーダプログラムビルド
// return ビルド結果生成されるシェーダオブジェクト / 失敗時は0を返却
//----------------------------------------------------------------------------//
GLuint BuildShaderProgram(const char* fragshader)
{
    // 頂点シェーダコンパイル
    GLuint vshaderId = CompileShaderProgram(GL_VERTEX_SHADER, gsc_pszVShader);
    __android_log_print(ANDROID_LOG_ERROR, "GLES2Sample1", "vshder");
    if (vshaderId == 0) {
        return 0;
    }

    // フラグメントシェーダコンパイル
    GLuint fshaderId = CompileShaderProgram(GL_FRAGMENT_SHADER, fragshader);
    __android_log_print(ANDROID_LOG_ERROR, "GLES2Sample1", "fshader");
    if (fshaderId == 0) {
        return 0;
    }

    // シェーダプログラム作成
    GLuint programId = glCreateProgram();

    // 頂点、フラグメント両シェーダをアタッチ
    glAttachShader(programId, fshaderId);
    glAttachShader(programId, vshaderId);

    // a_pos変数を番号に割り当て
    glBindAttribLocation(programId, ATTR_POS, "a_pos");

    // プログラムをリンク
    glLinkProgram(programId);

    // リンクエラー判定
    GLint bLinked;
    glGetProgramiv(programId, GL_LINK_STATUS, &bLinked);
    if (!bLinked)
    {
        __android_log_print(ANDROID_LOG_ERROR, "GLES2Sample1", "シェーダリンクに失敗");
        return 0;
    }

    // リンクに使用した頂点、フラグメント各シェーダオブジェクトは不要な為削除
    glDeleteShader(vshaderId);
    glDeleteShader(fshaderId);

    return programId;
}

// 三角形頂点データ
static const GLfloat vertexs_1[] = {
//        -0.5f, -0.5f, 0.0f,    // 左下
//        0.5f, -0.5f, 0.0f,    // 右下
//        0.0f,  0.5f, 0.0f    // 上
};

static const GLfloat vertexs_2[] = {
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.0f, -0.5f, 0.0f
};

GLuint shaderProg;
GLuint shaderProgr;

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_com_mikn_high_1rgb_1finder_JNIBridge_onSurfaceCreatedNdk(JNIEnv *env, jclass clazz) {
    // シェーダプログラムビルド
    shaderProg = BuildShaderProgram(gsc_pszFShader_1);
    if (shaderProg == 0) {
        // TODO:エラー処理
        return;
    }

    shaderProgr = BuildShaderProgram(gsc_pszFShader_2);
    if (shaderProg == 0) {
        // TODO:エラー処理
        return;
    }

    // ビルドしたシェーダプログラムを選択

    // 頂点データ設定
    glEnableVertexAttribArray(ATTR_POS);
}

JNIEXPORT void JNICALL Java_com_mikn_high_1rgb_1finder_JNIBridge_onSurfaceChangedNdk(JNIEnv *env, jclass clazz, jint width, jint height) {
    // ビューポートを設定します。
    glViewport(0, 0, width, height);
}

JNIEXPORT void JNICALL Java_com_mikn_high_1rgb_1finder_JNIBridge_onDrawFrameNdk(JNIEnv *env, jclass clazz) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //三角形描画
    glUseProgram(shaderProg);
    glVertexAttribPointer(ATTR_POS, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, vertexs_1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexAttribPointer(ATTR_POS, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, vertexs_2);
    glUseProgram(shaderProgr);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
#ifdef __cplusplus
}
#endif