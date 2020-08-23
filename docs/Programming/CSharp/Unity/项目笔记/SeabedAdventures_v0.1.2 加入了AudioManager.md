AudioManager.cs 代码：
```csharp
using UnityEngine;

namespace SeabedAdventures {
    public class AudioManager : MonoBehaviour {
        private       AudioListener mAudioListener;
        public static AudioManager  Instance;

        private void Start() {
            
        }

        private void OnEnable() {
            Instance = this; 
        }

        void CheckAudioListener() {
            if (!mAudioListener) {
                mAudioListener = FindObjectOfType<AudioListener>();
            }

            if (!mAudioListener) {
                mAudioListener = gameObject.AddComponent<AudioListener>();
            }
        }

        public void PlaySound(string soundName) {
            CheckAudioListener();

            var coinClip    = Resources.Load<AudioClip>(soundName);
            var audioSource = gameObject.AddComponent<AudioSource>();

            audioSource.clip = coinClip;
            audioSource.Play();
        }

        private AudioSource mMusicSource;

        public void PlayMusic(string musicName, bool loop) {
            CheckAudioListener();

            if (!mMusicSource) {
                mMusicSource = gameObject.AddComponent<AudioSource>();
            }

            var coinClip = Resources.Load<AudioClip>(musicName);

            mMusicSource.clip = coinClip;
            mMusicSource.loop = loop;
            mMusicSource.Play();
        }

        public void StopMusic() {
            mMusicSource.Stop();
        }

        public void PauseMusic() {
            mMusicSource.Pause();
        }

        public void ResumeMusic() {
            mMusicSource.UnPause();
        }

        public void MusicOff() {
            mMusicSource.Pause();
            mMusicSource.mute = true;
        }

        public void SoundOff() {
            var soundSources = GetComponents<AudioSource>();

            foreach (var soundSource in soundSources) {
                if (soundSource != mMusicSource) {
                    soundSource.Pause();
                    soundSource.mute = true;
                }
            }
        }

        public void MusicOn() {
            mMusicSource.UnPause();
            mMusicSource.mute = false;
        }

        public void SoundOn() {
            var soundSources = GetComponents<AudioSource>();

            foreach (var soundSource in soundSources) {
                if (soundSource != mMusicSource) {
                    soundSource.UnPause();
                    soundSource.mute = false;
                }
            }
        }

        /// <summary>
        /// 设置音乐声音大小，0到1之间
        /// </summary>
        /// <param name="volume"></param>
        public void SetMusicVolume(float volume) {
            mMusicSource.volume = volume;
        }
    }
}
```
## 说明
由于游戏有两个场景，所以，AudioManager物体不能在加载到第二个场景后被销毁，可以在`Start()`方法中调用`DontDestroyOnLoad`方法：
```
void Start(){
//...
    DontDestroyOnLoad(transform.gameObject);
//...
}
```
但是当游戏结束后，重新加载游戏时，第二个场景中的未被销毁的`AudioManager`会再出现重新加载后的第一个场景。那么就会出现两个AudioManager。
但不影响游戏效果。

为解决这个问题，不再在Start中调用DontDestroyOnLoad方法，而是在第二个场景中也创建一个AudioManager物体。
这里又出现了调用顺序的问题。
经过一番尝试后，把单的例的赋值操作放在了`Onnable();`中。
