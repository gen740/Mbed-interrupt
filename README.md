# Mbed_OS Interrupt + BLE のサンプルプロジェクト
　これは、mbed os のInterruptとBLEを用いたサンプルのプロジェクトです。
Mbed CLIを利用することを前提としています。

## プログラムの実行
- Mbed OS対応のマイコンをUSB等でパソコンに接続します
```zsh
mbed-tools detect
```

コマンドで、マイコンを探します。
`mbed-tools`コマンドは、`pip install mbed-tools`でインストールすることができます
- 上のコマンドで、表示されたTargetを用いて以下のコマンドを実行します
```zsh
mbed-tools configure -m Target -t GCC_ARM
```
- コンパイルには
```zsh
mbed-tools compile -m Target -t GCC_ARM
```
のコマンドを使います。

- 書き込む場合は`-f`のオプションを用い
```zsh
mbed-tools compile -m Target -t GCC_ARM -f
```
を使います

