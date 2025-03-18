using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class collectible : MonoBehaviour
{
    public AudioSource sound;
    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player") {
            player Player = FindObjectOfType<player>();
            Player.jav_size += 0.5f;
            Destroy(gameObject);
            sound.Play(0);
        }
    }

    void Update()
    {
        transform.Rotate(0f, 0f, 75f * Time.deltaTime);
    }
}
