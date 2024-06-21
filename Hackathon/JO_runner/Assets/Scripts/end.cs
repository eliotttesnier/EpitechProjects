using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class end : MonoBehaviour
{
    public AudioSource cheer;
    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player") {
            player Player = FindObjectOfType<player>();
            Player.finish = true;
            cheer.Play(0);
        }
    }
}
